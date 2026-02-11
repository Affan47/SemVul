OnLayout(GF_SensorHandler *sh, Bool is_over, Bool is_cancel, GF_Event *ev, GF_Compositor *compositor)
{
	Bool vertical = ((M_Layout *)sh->sensor)->scrollVertical;
	LayoutStack *st = (LayoutStack *) gf_node_get_private(sh->sensor);

	if (!is_over) {
		st->is_scrolling = 0;
		st->key_scroll = 0;
		return 0;
	}
	if (ev->type!=GF_EVENT_KEYDOWN) {
		st->is_scrolling = 0;
		st->key_scroll = 0;
		return 0;
	}

	switch (ev->key.key_code) {
	case GF_KEY_LEFT:
		if (vertical) return 0;
		st->key_scroll = -1;
		break;
	case GF_KEY_RIGHT:
		if (vertical) return 0;
		st->key_scroll = +1;
		break;
	case GF_KEY_UP:
		if (!vertical) return 0;
		st->key_scroll = +1;
		break;
	case GF_KEY_DOWN:
		if (!vertical) return 0;
		st->key_scroll = -1;
		break;
	default:
		st->key_scroll = 0;
		return 0;
	}
	gf_sc_invalidate(compositor, NULL);
	return 1;
}
