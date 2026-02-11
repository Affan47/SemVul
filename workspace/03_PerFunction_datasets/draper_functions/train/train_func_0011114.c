bttv_irq_wakeup_vbi(struct bttv *btv, struct bttv_buffer *wakeup,
		    unsigned int state)
{
	if (NULL == wakeup)
		return;

	v4l2_get_timestamp(&wakeup->vb.ts);
	wakeup->vb.field_count = btv->field_count;
	wakeup->vb.state = state;
	wake_up(&wakeup->vb.done);
}
