local_queue_frame(struct local_pvt *p, int isoutbound, struct ast_frame *f,
	struct ast_channel *us, int us_locked)
{
	struct ast_channel *other = NULL;


	other = isoutbound ? p->owner : p->chan;

	if (!other) {
		return 0;
	}


	if (us && ast_channel_generator(us) && ast_channel_generator(other)) {
		return 0;
	}


	ast_channel_ref(other);
	if (us && us_locked) {
		ast_channel_unlock(us);
	}
	ao2_unlock(p);

	if (f->frametype == AST_FRAME_CONTROL && f->subclass.integer == AST_CONTROL_RINGING) {
		ast_setstate(other, AST_STATE_RINGING);
	}
	ast_queue_frame(other, f);

	other = ast_channel_unref(other);
	if (us && us_locked) {
		ast_channel_lock(us);
	}
	ao2_lock(p);

	return 0;
}
