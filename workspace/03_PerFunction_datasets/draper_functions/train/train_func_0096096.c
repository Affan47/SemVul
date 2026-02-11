write_jt_match_record(struct libjte_env *o,
                           char *filename, char *mirror_name, int sector_size,
                           off_t size, unsigned char md5[16])
{
    char                buf[32768];
    off_t               remain = size;
	FILE               *infile = NULL;
	int	                use = 0;
    uint64_t  rsync64_sum = 0;
    int first_block = 1;

    memset(buf, 0, sizeof(buf));

    if ((infile = fopen(filename, "rb")) == NULL) {
#ifndef	HAVE_STRERROR
		sprintf(o->message_buffer, "cannot open '%s': (%d)",
				filename, errno);
#else
		sprintf(o->message_buffer, "cannot open '%s': %s",
				filename, strerror(errno));
#endif
                libjte_add_msg_entry(o, o->message_buffer, 0);
		exit_if_enabled(o, 1);
		return -1;
	}

    while (remain > 0)
    {
        use = remain;
        if (remain > sizeof(buf))
            use = sizeof(buf);
		if (fread(buf, 1, use, infile) == 0)
        {
			sprintf(o->message_buffer,
                                "cannot read from '%s'", filename);
                        libjte_add_msg_entry(o, o->message_buffer, 0);
			exit_if_enabled(o, 1);
			return -1;
	}
        if (first_block)
            rsync64_sum = rsync64((unsigned char *) buf, MIN_JIGDO_FILE_SIZE);
        checksum_update(o->iso_context, (unsigned char *) buf, use);
        remain -= use;
        first_block = 0;
    }

    fclose(infile);


    if (size % sector_size)
    {
        int pad_size = sector_size - (size % sector_size);
        memset(buf, 0, pad_size);
        checksum_update(o->iso_context, (unsigned char *) buf, pad_size);
    }

    add_file_entry(o, mirror_name, size, &md5[0], rsync64_sum);
    if (size % sector_size)
    {
        int pad_size = sector_size - (size % sector_size);
        write_compressed_chunk(o, (unsigned char *) buf, pad_size);
        add_unmatched_entry(o, pad_size);
    }
    return 1;
}
