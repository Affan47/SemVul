set_o_direct(int dev, unsigned char *buffer, size_t size,
			 blk_t current_block)
{
#ifdef O_DIRECT
	int new_flag = O_DIRECT;
	int flag;

	if ((((unsigned long) buffer & (sys_page_size - 1)) != 0) ||
	    ((size & (sys_page_size - 1)) != 0) ||
	    ((current_block & ((sys_page_size >> 9)-1)) != 0))
		new_flag = 0;

	if (new_flag != current_O_DIRECT) {

		flag = fcntl(dev, F_GETFL);
		if (flag > 0) {
			flag = (flag & ~O_DIRECT) | new_flag;
			fcntl(dev, F_SETFL, flag);
		}
		current_O_DIRECT = new_flag;
	}
#endif
}
