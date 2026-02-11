shuttle_open(shuttle_data_t* shuttle){
	if (shuttle != NULL){
		int i = 0;
  		char name[256] = "unknown";
		char *device;
		char shuttlename[256] = "Contour Design ShuttleXpress";

		device = malloc(18 * sizeof(char));
		if (shuttle->fd) close(shuttle->fd);
		shuttle->fd = 0;

		for (i = 0;(i < 10) && !shuttle->fd;i++){
			snprintf(device,18,"/dev/input/event%d",i);
			shuttle->fd = open(device, O_RDONLY);
			if (shuttle->fd > 0){
				if (ioctl(shuttle->fd, EVIOCGNAME(sizeof(name)), name) < 0){
					shuttle->fd = close (shuttle->fd);
				}else{
					if (strncmp(name,shuttlename,22) != 0){
						shuttle->fd = close (shuttle->fd);
					}else{

					}
				}
			}else{shuttle->fd = 0;}
		}
		return shuttle->fd;
	}
	return 0;
}
