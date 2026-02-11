shuttle_close (shuttle_data_t* shuttle){
	if (shuttle != NULL){
		if (shuttle->fd > 0){
	 		shuttle->fd = close(shuttle->fd);
			printf ("Shuttle device closed\n");
		}
		return shuttle->fd;
	}else return -1;
}
