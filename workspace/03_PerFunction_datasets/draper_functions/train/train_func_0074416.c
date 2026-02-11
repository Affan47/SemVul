read_string_file(int fd,char *dest, int dest_size)
{
    unsigned char len;

    if (read(fd,&len,1) != 1) {
	fprintf(stderr,"File truncated\n");
	exit(1);
    }
    if (len+1 > dest_size) {
	fprintf(stderr,"Text too large; size %d, max is %d\n",
						len, dest_size-1);
	exit(1);
    }
    if (len > 0) {
	if (read(fd,dest,len) != len) {
	    fprintf(stderr,"File truncated\n");
	    exit(1);
	}
    }
    dest[len] = '\0';
}
