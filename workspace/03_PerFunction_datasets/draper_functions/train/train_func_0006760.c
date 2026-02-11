bttv_irq_next_video(struct bttv *btv, struct bttv_buffer_set *set)
{
	struct bttv_buffer *item;

	memset(set,0,sizeof(*set));


	if (!list_empty(&btv->capture)) {
		set->frame_irq = 1;
		item = list_entry(btv->capture.next, struct bttv_buffer, vb.queue);
		if (V4L2_FIELD_HAS_TOP(item->vb.field))
			set->top    = item;
		if (V4L2_FIELD_HAS_BOTTOM(item->vb.field))
			set->bottom = item;


		if (!V4L2_FIELD_HAS_BOTH(item->vb.field) &&
		    (item->vb.queue.next != &btv->capture)) {
			item = list_entry(item->vb.queue.next, struct bttv_buffer, vb.queue);


			if (!V4L2_FIELD_HAS_BOTH(item->vb.field)) {
				if (NULL == set->bottom &&
				    V4L2_FIELD_BOTTOM == item->vb.field) {
					set->bottom = item;
				}
				if (NULL != set->top  &&  NULL != set->bottom)
					set->top_irq = 2;
			}
		}
	}


	if (NULL != btv->screen) {
		if (V4L2_FIELD_HAS_BOTH(btv->screen->vb.field)) {
			if (NULL == set->top && NULL == set->bottom) {
				set->top    = btv->screen;
				set->bottom = btv->screen;
			}
		} else {
			if (V4L2_FIELD_TOP == btv->screen->vb.field &&
			    NULL == set->top) {
				set->top = btv->screen;
			}
			if (V4L2_FIELD_BOTTOM == btv->screen->vb.field &&
			    NULL == set->bottom) {
				set->bottom = btv->screen;
			}
		}
	}

	dprintk("%d: next set: top=%p bottom=%p [screen=%p,irq=%d,%d]\n",
		btv->c.nr, set->top, set->bottom,
		btv->screen, set->frame_irq, set->top_irq);
	return 0;
}
