__open_metadata(struct dm_pool_metadata *pmd)
{
	int r;
	struct dm_block *sblock;
	struct thin_disk_superblock *disk_super;

	r = dm_bm_read_lock(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			    &sb_validator, &sblock);
	if (r < 0) {
		DMERR("couldn't read superblock");
		return r;
	}

	disk_super = dm_block_data(sblock);


	if (le32_to_cpu(disk_super->data_block_size) != pmd->data_block_size) {
		DMERR("changing the data block size (from %u to %llu) is not supported",
		      le32_to_cpu(disk_super->data_block_size),
		      (unsigned long long)pmd->data_block_size);
		r = -EINVAL;
		goto bad_unlock_sblock;
	}

	r = __check_incompat_features(disk_super, pmd);
	if (r < 0)
		goto bad_unlock_sblock;

	r = dm_tm_open_with_sm(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			       disk_super->metadata_space_map_root,
			       sizeof(disk_super->metadata_space_map_root),
			       &pmd->tm, &pmd->metadata_sm);
	if (r < 0) {
		DMERR("tm_open_with_sm failed");
		goto bad_unlock_sblock;
	}

	pmd->data_sm = dm_sm_disk_open(pmd->tm, disk_super->data_space_map_root,
				       sizeof(disk_super->data_space_map_root));
	if (IS_ERR(pmd->data_sm)) {
		DMERR("sm_disk_open failed");
		r = PTR_ERR(pmd->data_sm);
		goto bad_cleanup_tm;
	}

	pmd->nb_tm = dm_tm_create_non_blocking_clone(pmd->tm);
	if (!pmd->nb_tm) {
		DMERR("could not create non-blocking clone tm");
		r = -ENOMEM;
		goto bad_cleanup_data_sm;
	}

	__setup_btree_details(pmd);
	dm_bm_unlock(sblock);

	return 0;

bad_cleanup_data_sm:
	dm_sm_destroy(pmd->data_sm);
bad_cleanup_tm:
	dm_tm_destroy(pmd->tm);
	dm_sm_destroy(pmd->metadata_sm);
bad_unlock_sblock:
	dm_bm_unlock(sblock);

	return r;
}
