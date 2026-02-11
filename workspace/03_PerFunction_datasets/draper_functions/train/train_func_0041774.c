ipmi_write(struct file *file,
			  const char  __user *buf,
			  size_t      len,
			  loff_t      *ppos)
{
	int rv;

	if (len) {
		if (!nowayout) {
			size_t i;


			expect_close = 0;

			for (i = 0; i != len; i++) {
				char c;

				if (get_user(c, buf + i))
					return -EFAULT;
				if (c == 'V')
					expect_close = 42;
			}
		}
		rv = ipmi_heartbeat();
		if (rv)
			return rv;
	}
	return len;
}
