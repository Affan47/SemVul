wait() {
  pipe_fifo.make_readonly();
  char letter;
  while (::read(pipe_fifo.get_read_fd(), &letter, 1) == -1
	 && errno == EINTR);
  pipe_fifo.make_writeonly();
}

}
