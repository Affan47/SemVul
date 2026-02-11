syncDisk()
{
	int result;


	result = fsync(fd);

	if(result == -1){
		perror("Error synchronizing to disk");
	}
}
