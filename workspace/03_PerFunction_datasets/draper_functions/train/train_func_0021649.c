write_dlb_directory(out, nfiles, ld, slen, dir_size, flen)
int out, nfiles;
libdir *ld;
long slen, dir_size, flen;
{
    char buf[BUFSIZ];
    int i;

    sprintf(buf,"%3ld %8ld %8ld %8ld %8ld\n",
	    (long) DLB_VERS,
	    (long) nfiles+1,

	    (long) slen+strlen(DLB_DIRECTORY)+nfiles+1,
	    (long) dir_size,
	    (long) flen+dir_size);
    Write(out, buf, strlen(buf));


#define ENTRY_FORMAT "%c%s %8ld\n"
    sprintf(buf, ENTRY_FORMAT, ENC_NORMAL, DLB_DIRECTORY, (long) 0);
    Write(out, buf, strlen(buf));
    for (i = 0; i < nfiles; i++) {
	sprintf(buf, ENTRY_FORMAT,
		ENC_NORMAL,
		ld[i].fname,
		ld[i].foffset + dir_size);
	Write(out, buf, strlen(buf));
    }
}
