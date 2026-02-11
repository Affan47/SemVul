sel_read_handle_unknown(struct file *filp, char __user *buf,
					size_t count, loff_t *ppos)
{
	char tmpbuf[TMPBUFLEN];
	ssize_t length;
	ino_t ino = file_inode(filp)->i_ino;
	int handle_unknown = (ino == SEL_REJECT_UNKNOWN) ?
		security_get_reject_unknown() : !security_get_allow_unknown();

	length = scnprintf(tmpbuf, TMPBUFLEN, "%d", handle_unknown);
	return simple_read_from_buffer(buf, count, ppos, tmpbuf, length);
}
