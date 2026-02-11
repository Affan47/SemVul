load_data_v1(struct map_hdr_v1 *hdr, u_long index, u_long *buf, u_long *len)
{
	char *compr_buf;
	char *exp_buf;
	int ret, items;
	uLongf destLen;

	if(hdr->map[index].exp_data)
		goto out;
	ret = fseek(vas_file_p, (long)((hdr->blk_offset + hdr->map[index].start_blk) * hdr->blk_size),
		    SEEK_SET);

	if(ret == -1) {
		printf("load_data: unable to fseek, errno = %d\n", ferror(vas_file_p));
		clean_exit(1);
	}
	compr_buf =  (char *)malloc(2*hdr->va_per_entry);
	if(!compr_buf) {
		printf("load_data: bad ret from malloc, errno = %d\n", ferror(vas_file_p));
		clean_exit(1);
	}
	items = fread((void *)compr_buf, sizeof(char), hdr->map[index].num_blks * hdr->blk_size, vas_file_p);
	if(items != hdr->map[index].num_blks * hdr->blk_size) {
		printf("unable to read blocks from errno = %d\n", ferror(vas_file_p));
		clean_exit(1);
	}
	hdr->map[index].exp_data = exp_buf =  (char *)malloc(hdr->va_per_entry);
	if(!exp_buf) {
		printf("load_data: bad ret from malloc, errno = %d\n", ferror(vas_file_p));
		clean_exit(1);
	}
	destLen = (uLongf)(2*hdr->va_per_entry);
	ret = uncompress((Bytef *)exp_buf, &destLen, (const Bytef *)compr_buf, (uLong)items);


	if(ret) {
		if(ret == Z_MEM_ERROR)
			printf("load_data, bad ret Z_MEM_ERROR from uncompress\n");
		else if(ret == Z_BUF_ERROR)
			printf("load_data, bad ret Z_BUF_ERROR from uncompress\n");
		else if(ret == Z_DATA_ERROR)
			printf("load_data, bad ret Z_DATA_ERROR from uncompress\n");
		else
			printf("load_data, bad ret %d from uncompress\n", ret);

		clean_exit(1);
	}
	free((void *)compr_buf);
  out:
	if(buf)
		*buf = (u_long)hdr->map[index].exp_data;
	if(len)
		*len = hdr->va_per_entry;
	return;
}
