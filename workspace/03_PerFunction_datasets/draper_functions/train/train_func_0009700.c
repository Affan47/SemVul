mohalloc(struct mohclass *cl)
{
	struct mohdata *moh;
	long flags;

	if (!(moh = ast_calloc(1, sizeof(*moh))))
		return NULL;

	if (pipe(moh->pipe)) {
		ast_log(LOG_WARNING, "Failed to create pipe: %s\n", strerror(errno));
		ast_free(moh);
		return NULL;
	}


	flags = fcntl(moh->pipe[0], F_GETFL);
	fcntl(moh->pipe[0], F_SETFL, flags | O_NONBLOCK);
	flags = fcntl(moh->pipe[1], F_GETFL);
	fcntl(moh->pipe[1], F_SETFL, flags | O_NONBLOCK);

	moh->f.frametype = AST_FRAME_VOICE;
	ast_format_copy(&moh->f.subclass.format, &cl->format);
	moh->f.offset = AST_FRIENDLY_OFFSET;

	moh->parent = mohclass_ref(cl, "Reffing music class for mohdata parent");

	ao2_lock(cl);
	AST_LIST_INSERT_HEAD(&cl->members, moh, list);
	ao2_unlock(cl);

	return moh;
}
