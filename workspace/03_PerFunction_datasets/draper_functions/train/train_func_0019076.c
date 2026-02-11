dump_metadata_block(FILE *out_file, struct journal_source *source,
				journal_superblock_t *jsb EXT2FS_ATTR((unused)),
				unsigned int log_blocknr,
				unsigned int fs_blocknr,
				unsigned int log_tag_flags,
				int blocksize,
				tid_t transaction)
{
	unsigned int 	got;
	int		retval;
	char 		buf[8192];

	if (!(dump_all
	      || (fs_blocknr == block_to_dump)
	      || (fs_blocknr == inode_block_to_dump)
	      || (fs_blocknr == bitmap_to_dump)))
		return;

	fprintf(out_file, "  FS block %u logged at ", fs_blocknr);
	if (!dump_all)
		fprintf(out_file, "sequence %u, ", transaction);
	fprintf(out_file, "journal block %u (flags 0x%x)\n", log_blocknr,
		log_tag_flags);


	if (!(dump_contents && dump_all)
	    && fs_blocknr != block_to_dump
	    && fs_blocknr != bitmap_to_dump
	    && fs_blocknr != inode_block_to_dump)
		return;

	retval = read_journal_block("logdump", source,
				    blocksize * log_blocknr,
				    buf, blocksize, &got);
	if (retval)
		return;

	if (fs_blocknr == bitmap_to_dump) {
		struct ext2_super_block *super;
		int offset;

		super = current_fs->super;
		offset = ((block_to_dump - super->s_first_data_block) %
			  super->s_blocks_per_group);

		fprintf(out_file, "    (block bitmap for block %u: "
			"block is %s)\n",
			block_to_dump,
			ext2fs_test_bit(offset, buf) ? "SET" : "CLEAR");
	}

	if (fs_blocknr == inode_block_to_dump) {
		struct ext2_inode *inode;
		int first, prev, this, start_extent, i;

		fprintf(out_file, "    (inode block for inode %u):\n",
			inode_to_dump);

		inode = (struct ext2_inode *) (buf + inode_offset_to_dump);
		internal_dump_inode(out_file, "    ", inode_to_dump, inode, 0);


		fprintf (out_file, "    Blocks:  ");
		first = prev = start_extent = -1;

		for (i=0; i<EXT2_NDIR_BLOCKS; i++) {
			this = inode->i_block[i];
			if (start_extent >= 0  && this == prev+1) {
				prev = this;
				continue;
			} else {
				show_extent(out_file, start_extent, i, first);
				start_extent = i;
				first = prev = this;
			}
		}
		show_extent(out_file, start_extent, i, first);
		show_indirect(out_file, "IND", inode->i_block[i++]);
		show_indirect(out_file, "DIND", inode->i_block[i++]);
		show_indirect(out_file, "TIND", inode->i_block[i++]);

		fprintf(out_file, "\n");
	}

	if (dump_contents)
		do_hexdump(out_file, buf, blocksize);

}
