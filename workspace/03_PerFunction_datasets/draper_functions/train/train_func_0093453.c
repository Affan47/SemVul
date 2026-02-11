ng_process_get_frame(struct ng_process_handle *h)
{
    struct ng_video_buf *buf = NULL;

    switch (h->p->mode) {
    case NG_MODE_TRIVIAL:
	BUG_ON(NULL == h->get, "no setup");
	if (NULL != h->in) {
	    buf = h->get(h->ghandle, &h->ofmt);
#if 0
	    ng_print_video_buf("in",h->in);
	    ng_print_video_buf("out",buf);
#endif
	    h->p->frame(h->phandle, buf, h->in);
	    buf->info = h->in->info;
	    ng_release_video_buf(h->in);
	    h->in = NULL;
	}
	break;
    case NG_MODE_COMPLEX:
	buf = h->p->get_frame(h->phandle);
	break;
    default:
	BUG_ON(1,"mode not implemented yet");
	break;
    }
    return buf;
}
