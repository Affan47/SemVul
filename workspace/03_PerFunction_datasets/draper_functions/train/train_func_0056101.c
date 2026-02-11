run(bool modal)
{
	ht_view *orig_focused=app->getselected(), *orig_baseview=baseview;
	int oldx, oldy;
	ht_view *drawer=modal ? this : app;
	screen->getCursor(oldx, oldy);
	setstate(ds_normal, 0);
	((ht_group*)app)->insert(this);
	((ht_group*)app)->focus(this);
	baseview = this;
	drawer->sendmsg(msg_draw, 0);
	screen->show();
	while (getstate(0) == ds_normal) {
		if (keyb_keypressed()) {
			ht_key k = keyb_getkey();
			sendmsg(msg_keypressed, k);
			drawer->sendmsg(msg_draw, 0);
			screen->show();
		}
		if (sys_get_winch_flag()) {
			do_modal_resize();
		}
		ht_queued_msg *q;
		while ((q = dequeuemsg())) {
			htmsg m = q->msg;
			q->target->sendmsg(&m);
			sendmsg(msg_draw);
			delete q;
		}
		if (!modal) do_idle();
	}
	int return_val;
	int state = getstate(&return_val);
	screen->setCursor(oldx, oldy);
	((ht_group*)app)->remove(this);
	app->focus(orig_focused);
	baseview = orig_baseview;
	if (state != ds_term_cancel) {
		return return_val;
	} else {
		return 0;
	}
}
