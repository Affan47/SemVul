write_manifest(gzFile f, const struct manifest *mf)
{
	uint16_t i, j;

	WRITE_INT(4, MAGIC);
	WRITE_INT(1, VERSION);
	WRITE_INT(1, 16);
	WRITE_INT(2, 0);

	WRITE_INT(4, mf->n_files);
	for (i = 0; i < mf->n_files; i++) {
		WRITE_STR(mf->files[i]);
	}

	WRITE_INT(4, mf->n_file_infos);
	for (i = 0; i < mf->n_file_infos; i++) {
		WRITE_INT(4, mf->file_infos[i].index);
		WRITE_BYTES(mf->hash_size, mf->file_infos[i].hash);
		WRITE_INT(4, mf->file_infos[i].size);
	}

	WRITE_INT(4, mf->n_objects);
	for (i = 0; i < mf->n_objects; i++) {
		WRITE_INT(4, mf->objects[i].n_file_info_indexes);
		for (j = 0; j < mf->objects[i].n_file_info_indexes; j++) {
			WRITE_INT(4, mf->objects[i].file_info_indexes[j]);
		}
		WRITE_BYTES(mf->hash_size, mf->objects[i].hash.hash);
		WRITE_INT(4, mf->objects[i].hash.size);
	}

	return 1;

error:
	cc_log("Error writing to manifest file");
	return 0;
}
