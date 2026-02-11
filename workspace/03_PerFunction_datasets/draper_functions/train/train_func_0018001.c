qt_vdata(void *handle, unsigned int drop)
{
    struct qt_handle *h = handle;
    struct ng_video_buf *buf;
    unsigned int i;

    if (quicktime_video_position(h->qt,0) >= quicktime_video_length(h->qt,0))
	return NULL;

    buf = ng_malloc_video_buf(&h->vfmt,h->vfmt.bytesperline*h->vfmt.height);
    if (!h->rows)
	h->rows = malloc(h->vfmt.height * sizeof(char*));
    switch (fmtid_to_cmodel[h->vfmt.fmtid]) {
    case BC_RGB888:
    case BC_BGR888:
	for (i = 0; i < h->vfmt.height; i++)
	    h->rows[i] = buf->data + h->vfmt.width * 3 * i;
	break;
    case BC_YUV422:
	for (i = 0; i < h->vfmt.height; i++)
	    h->rows[i] = buf->data+ h->vfmt.width * 2 * i;
	break;
    case BC_YUV420P:
	h->rows[0] = buf->data;
	h->rows[1] = buf->data + h->vfmt.width*h->vfmt.height;
	h->rows[2] = buf->data + h->vfmt.width*h->vfmt.height*5/4;
	break;
    default:
	BUG_ON(1,"unknown cmodel");
    }


    for (i = 0; i < drop; i++)
	quicktime_read_frame(h->qt,buf->data,0);

    buf->info.seq  = quicktime_video_position(h->qt,0);
    buf->info.ts   = (long long) buf->info.seq * 1000000000 / h->rate;
    lqt_decode_video(h->qt, h->rows, 0);
    return buf;
}
