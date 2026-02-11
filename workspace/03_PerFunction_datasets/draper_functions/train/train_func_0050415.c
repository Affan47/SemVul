cst_wave_append_riff(cst_wave *w,const char *filename)
{

    cst_file fd;
    cst_wave_header hdr;
    char info[4];
    int d_int;
    int rv, num_bytes, n, sample_rate;

    if ((fd = cst_fopen(filename,CST_OPEN_WRITE|CST_OPEN_READ|CST_OPEN_BINARY)) == NULL)
    {
	cst_errmsg("cst_wave_append: can't open file \"%s\"\n",
		   filename);
	return -1;
    }

    rv = cst_wave_load_riff_header(&hdr,fd);
    if (rv != CST_OK_FORMAT)
    {
	cst_fclose(fd);
	return rv;
    }

    cst_fread(fd,info,1,4);
    cst_fread(fd,&d_int,4,1);
    if (CST_BIG_ENDIAN) d_int = SWAPINT(d_int);
    hdr.num_samples = d_int/sizeof(short);

    cst_fseek(fd,
	      cst_ftell(fd)+(hdr.hsize-16)+
	      (hdr.num_samples*hdr.num_channels*sizeof(short)),
	      CST_SEEK_ABSOLUTE);

    if (CST_BIG_ENDIAN)
    {
	short *xdata = cst_alloc(short,cst_wave_num_channels(w)*
				 cst_wave_num_samples(w));
	memmove(xdata,cst_wave_samples(w),
		sizeof(short)*cst_wave_num_channels(w)*
		cst_wave_num_samples(w));
	swap_bytes_short(xdata,
			 cst_wave_num_channels(w)*
			 cst_wave_num_samples(w));
	n = cst_fwrite(fd,xdata,sizeof(short),
		       cst_wave_num_channels(w)*cst_wave_num_samples(w));
	cst_free(xdata);
    }
    else
    {
	n = cst_fwrite(fd,cst_wave_samples(w),sizeof(short),
		       cst_wave_num_channels(w)*cst_wave_num_samples(w));
    }

    cst_fseek(fd,4,CST_SEEK_ABSOLUTE);
    num_bytes = hdr.num_bytes + (n*sizeof(short));
    if (CST_BIG_ENDIAN) num_bytes = SWAPINT(num_bytes);
    cst_fwrite(fd,&num_bytes,4,1);
    cst_fseek(fd,4+4+4+4 +4+2+2 ,CST_SEEK_ABSOLUTE);
    sample_rate = w->sample_rate;
    if (CST_BIG_ENDIAN) sample_rate = SWAPINT(sample_rate);
    cst_fwrite(fd,&sample_rate,4,1);
    cst_fseek(fd,4+4+4+4+4+2+2+4+4+2+2+4,CST_SEEK_ABSOLUTE);
    num_bytes =
	(sizeof(short) * cst_wave_num_channels(w) * cst_wave_num_samples(w)) +
	(sizeof(short) * hdr.num_channels * hdr.num_samples);
    if (CST_BIG_ENDIAN) num_bytes = SWAPINT(num_bytes);
    cst_fwrite(fd,&num_bytes,4,1);
    cst_fclose(fd);

    return rv;
}
