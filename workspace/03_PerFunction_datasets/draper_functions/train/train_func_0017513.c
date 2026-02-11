kmc_press_record_ready_button(int fd)
{
	char w_buff[1];
	int wr_fd;

	w_buff[0] = '\x73';

	wr_fd = write(fd, w_buff,1);
	if (wr_fd < 0 ){
		perror("write error please retry\n");
		exit(1);
	}

	kmc_sleep();
}
