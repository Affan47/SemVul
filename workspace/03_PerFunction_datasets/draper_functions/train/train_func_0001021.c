copy_file_to_fd( pfs_file *file, int fd )
{
	pfs_ssize_t ractual, wactual, offset = 0;
	char buffer[BUFFER_SIZE];

	while(1) {
		ractual = file->read(buffer,sizeof(buffer),offset);
		if(ractual<=0) return ractual;

		wactual = full_pwrite64(fd,buffer,ractual,offset);
		if(wactual>=0) {
			offset += wactual;
		} else {
			return -1;
		}
	}
}
