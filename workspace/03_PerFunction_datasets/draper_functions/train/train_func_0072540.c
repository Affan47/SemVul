data_sd(SSCOP_DSC *dsc,int s,void *msg,int length)
{
    BUFFER *buf;

    if (NORM_RX(s) >= NORM_RX(dsc->vr_mr)) {
	if (NORM_RX(dsc->vr_h) < NORM_RX(dsc->vr_mr)) {
	    send_ustat(dsc,dsc->vr_h,dsc->vr_mr);
	    dsc->vr_h = dsc->vr_mr;
	}
	return;
    }
    if (s == dsc->vr_r) {
	if (dsc->ops->data_ind) dsc->ops->data_ind(dsc->user,msg,length,s);
	if (s == dsc->vr_h) {
	    dsc->vr_r = dsc->vr_h = MOD24(s+1);
	    update_vr_mr(dsc);
	    return;
	}
	while (1) {
	    INC24(dsc->vr_r);
	    update_vr_mr(dsc);
	    buf = queue_lookup(&dsc->rx_buf,dsc->vr_r);
	    if (!buf) break;
	    queue_remove(&dsc->rx_buf,buf);
	    if (dsc->ops->data_ind)
		dsc->ops->data_ind(dsc->user,buf->data,buf->length,buf->key);
	    buffer_discard(buf);
	}
	return;
    }
    buf = buffer_create(length,s);
    memcpy(buf->data,msg,length);
    if (s == dsc->vr_h) {
	queue_put(&dsc->rx_buf,buf);
	INC24(dsc->vr_h);
	return;
    }
    if (NORM_RX(dsc->vr_h) < NORM_RX(s)) {
	queue_put(&dsc->rx_buf,buf);
	send_ustat(dsc,dsc->vr_h,s);
	dsc->vr_h = MOD24(s+1);
	return;
    }
    if (!queue_lookup(&dsc->rx_buf,s)) queue_put(&dsc->rx_buf,buf);
    else {
	buffer_discard(buf);
	start_error_recov(dsc,'Q');
    }
}
