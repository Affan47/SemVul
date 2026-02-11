filter_ioctl(void *data, int code, void *call_data)
{
    struct filter_stream *fs = data;

    switch (code) {
    case DICO_IOCTL_BYTES_IN:
	*(off_t*)call_data = dico_stream_bytes_in(fs->transport);
	break;

    case DICO_IOCTL_BYTES_OUT:
	*(off_t*)call_data = dico_stream_bytes_out(fs->transport);
	break;

    default:
	errno = EINVAL;
	return -1;
    }
    return 0;
}
