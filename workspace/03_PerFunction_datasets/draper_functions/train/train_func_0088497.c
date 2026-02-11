saa7146_unregister_device(struct video_device *vfd, struct saa7146_dev *dev)
{
	DEB_EE("dev:%p\n", dev);

	video_unregister_device(vfd);
	return 0;
}
