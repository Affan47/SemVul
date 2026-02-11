__stdcon_read(struct file_info *fp, void *buf, size_t count)
{
    char *bufp = buf;
    size_t n = 0;
    char ch;

    (void)fp;

    while (n < count) {
	if (fp->i.nbytes) {
	    ch = *bufp++ = *fp->i.datap++;
	    fp->i.nbytes--;
	    n++;
	    if (ch == '\n')
		return n;
	} else {
	    fp->i.nbytes = __line_input(fp, fp->i.buf, MAXBLOCK, __rawcon_read);
	    fp->i.datap = fp->i.buf;

	    if (fp->i.nbytes == 0)
		return n;
	}
    }

    return n;
}
