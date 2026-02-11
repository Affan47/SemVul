v4l2_get_parm (struct v4l2_driver *drv)
{
	int ret;
	struct v4l2_captureparm *c;

	drv->parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if ((ret=xioctl(drv->fd,VIDIOC_G_PARM,&drv->parm))>=0) {
		c=&drv->parm.parm.capture;
		printf ("PARM: capability=%d, capturemode=%d, %.3f fps "
			"ext=%x, readbuf=%d\n",
			c->capability,
			c->capturemode,
			c->timeperframe.denominator*1./c->timeperframe.numerator,
			c->extendedmode, c->readbuffers);
	} else {
		ret=errno;

		perror ("VIDIOC_G_PARM");
	}

	return ret;
}
