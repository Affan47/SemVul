print_inline_journal_information(ext2_filsys fs)
{
	journal_superblock_t	*jsb;
	struct ext2_inode	inode;
	ext2_file_t		journal_file;
	errcode_t		retval;
	ino_t			ino = fs->super->s_journal_inum;
	char			buf[1024];
	__u32			*mask_ptr, mask, m;
	int			i, j, size, printed = 0;

	retval = ext2fs_read_inode(fs, ino,  &inode);
	if (retval) {
		com_err(program_name, retval,
			_("while reading journal inode"));
		exit(1);
	}
	retval = ext2fs_file_open2(fs, ino, &inode, 0, &journal_file);
	if (retval) {
		com_err(program_name, retval,
			_("while opening journal inode"));
		exit(1);
	}
	retval = ext2fs_file_read(journal_file, buf, sizeof(buf), 0);
	if (retval) {
		com_err(program_name, retval,
			_("while reading journal super block"));
		exit(1);
	}
	ext2fs_file_close(journal_file);
	jsb = (journal_superblock_t *) buf;
	if (be32_to_cpu(jsb->s_header.h_magic) != JFS_MAGIC_NUMBER) {
		fprintf(stderr,
			"Journal superblock magic number invalid!\n");
		exit(1);
	}
	printf(_("Journal features:        "));
	for (i=0, mask_ptr=&jsb->s_feature_compat; i <3; i++,mask_ptr++) {
		mask = be32_to_cpu(*mask_ptr);
		for (j=0,m=1; j < 32; j++, m<<=1) {
			if (mask & m) {
				printf(" %s", e2p_jrnl_feature2string(i, m));
				printed++;
			}
		}
	}
	if (printed == 0)
		printf(" (none)");
	printf("\n");
	fputs(_("Journal size:             "), stdout);
	if ((fs->super->s_feature_ro_compat &
	     EXT4_FEATURE_RO_COMPAT_HUGE_FILE) &&
	    (inode.i_flags & EXT4_HUGE_FILE_FL))
		size = inode.i_blocks / (fs->blocksize / 1024);
	else
		size = inode.i_blocks >> 1;
	if (size < 8192)
		printf("%uk\n", size);
	else
		printf("%uM\n", size >> 10);
	printf(_("Journal length:           %u\n"
		 "Journal sequence:         0x%08x\n"
		 "Journal start:            %u\n"),
	       (unsigned int)ntohl(jsb->s_maxlen),
	       (unsigned int)ntohl(jsb->s_sequence),
	       (unsigned int)ntohl(jsb->s_start));
}
