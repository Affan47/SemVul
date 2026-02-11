gsd_getimage(unsigned char **pixbuf, unsigned int *xsize,
		 unsigned int *ysize)
{
    GLuint l, r, b, t;


    GLint tmp[4];

    glGetIntegerv(GL_VIEWPORT, tmp);
    l = tmp[0];
    r = tmp[0] + tmp[2] - 1;
    b = tmp[1];
    t = tmp[1] + tmp[3] - 1;

    *xsize = r - l + 1;
    *ysize = t - b + 1;

    *pixbuf = (unsigned char *)G_malloc((*xsize) * (*ysize) * 4);

    if (!*pixbuf)
	return (0);

    glReadBuffer(GL_FRONT);


    glReadPixels(l, b, (r) - (l) + 1, (t) - (b) + 1, GL_RGBA,
		 GL_UNSIGNED_BYTE, *pixbuf);

    return (1);
}
