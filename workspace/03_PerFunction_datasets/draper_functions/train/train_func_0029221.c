ft_simpleimagemmap(filename, headptr, dataptr, data2dptr, prot, share)
     char         *filename;
     FITSHead     *headptr;
     void        **dataptr;
     void       ***data2dptr;
     int	   prot;
     int	   share;
{
	int file;

	char	name[FT_FILENAME];
	char	extn[FT_FILENAME];
	int	indx = 0;

	char	tail[FT_FILENAME];
	int	max = FT_FILENAME;

	char	*data;
	int	 size;
	int	 mode;

    ft_parsefilename(filename, name, extn, max, &indx, tail, max);

    if ( prot & PROT_WRITE ) {
	mode = O_RDWR;
    } else {
	mode = O_RDONLY;
    }

    if ( (file = open(name, mode)) == -1) {
	if ( headptr ) 	 *headptr   = NULL;
	if ( data2dptr ) *data2dptr = NULL;

	return 0;
    }


    size = _filesize(file);
    data = (char *) mmap(NULL, size, prot, share, file, 0);
    close(file);

    if ( data == (char *)-1 ) return 0;

    return ft_indxmemdata(data, size, FT_MMAP, extn, indx, headptr, dataptr, data2dptr);
}
