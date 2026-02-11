bc_testlist_emit(int fd, int *codep, bytecode_info_t *bc)
{
    int len = bc->data[(*codep)++].len;
    int i;
    int ret;
    int begin, end;
    int wrote = 2*sizeof(int);


    if(write_int(fd, len)== -1) return -1;


    begin = lseek(fd, 0, SEEK_CUR);
    lseek(fd, sizeof(int), SEEK_CUR);


    for(i=0; i < len; i++) {
	int nextcodep = bc->data[(*codep)++].jump;

	ret = bc_test_emit(fd, codep, bc);
	if(ret < 0 ) return -1;

	wrote+=ret;
	*codep = nextcodep;
    }
    end = lseek(fd, 0, SEEK_CUR);
    if (end < 0) return -1;


    lseek(fd,begin,SEEK_SET);
    if(write_int(fd, end) == -1) return -1;


    lseek(fd,end,SEEK_SET);

    return wrote;
}
