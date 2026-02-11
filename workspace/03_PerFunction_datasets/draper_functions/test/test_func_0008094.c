getdqbuf(size_t size)
{
	char *buf = kmalloc(size, GFP_NOFS);
	if (!buf)
		printk(KERN_WARNING
		       "VFS: Not enough memory for quota buffers.\n");
	return buf;
}
