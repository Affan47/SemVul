frame(void *handle, struct ng_video_buf *in)
{
    struct ng_video_buf *out;
    unsigned char *dst;
    unsigned char *src;
    unsigned int y,cnt;

    out = ng_malloc_video_buf(&in->fmt, in->fmt.height * in->fmt.bytesperline);
    out->info = in->info;

    dst = out->data;
    src = in->data;
    cnt = in->fmt.width * ng_vfmt_to_depth[in->fmt.fmtid] / 8;
    for (y = 0; y < in->fmt.height; y++) {
	switch (in->fmt.fmtid) {
	case VIDEO_GRAY:
	case VIDEO_BGR24:
	case VIDEO_RGB24:
	case VIDEO_BGR32:
	case VIDEO_RGB32:
	    gamma_bytes(dst,src,cnt);
	    break;
	case VIDEO_RGB15_NATIVE:
	    gamma_native_rgb15(dst,src,in->fmt.width);
	    break;
	case VIDEO_RGB16_NATIVE:
	    gamma_native_rgb16(dst,src,in->fmt.width);
	    break;
	}
	dst += out->fmt.bytesperline;
	src += in->fmt.bytesperline;
    }

    ng_release_video_buf(in);
    return out;
}
