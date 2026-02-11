send_message() {
	printf("Prompting for sending message [CTRL+U]...\n");
	if (write(socket_fd, &ctrl_u, 1)< 0) {
		perror("send message");
		exit(1);
	}
	usleep(100000);
}
