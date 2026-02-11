con_get_cmap(unsigned char __user *arg)
{
	int i, k;
	unsigned char colormap[3*16];

	console_lock();
	for (i = k = 0; i < 16; i++) {
		colormap[k++] = default_red[i];
		colormap[k++] = default_grn[i];
		colormap[k++] = default_blu[i];
	}
	console_unlock();

	if (copy_to_user(arg, colormap, sizeof(colormap)))
		return -EFAULT;

	return 0;
}
