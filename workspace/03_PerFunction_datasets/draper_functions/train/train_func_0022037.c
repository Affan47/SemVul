sprintf_gamma(struct fbtft_par *par, unsigned long *curves, char *buf)
{
	ssize_t len = 0;
	unsigned int i, j;

	mutex_lock(&par->gamma.lock);
	for (i = 0; i < par->gamma.num_curves; i++) {
		for (j = 0; j < par->gamma.num_values; j++)
			len += scnprintf(&buf[len], PAGE_SIZE,
			     "%04lx ", curves[i * par->gamma.num_values + j]);
		buf[len - 1] = '\n';
	}
	mutex_unlock(&par->gamma.lock);

	return len;
}
