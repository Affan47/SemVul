mixer_read_attr(struct ng_attribute *attr)
{
    struct mixer_handle *h = attr->handle;
    int vol;

    switch (attr->id) {
    case ATTR_ID_VOLUME:
	if (-1 == ioctl(h->mix,MIXER_READ(h->volctl),&h->volume))
	    perror("oss mixer read volume");
	vol = h->volume & 0x7f;
	return vol;
    case ATTR_ID_MUTE:
	return h->muted;
    default:
	return -1;
    }
}
