G_FreeEdict (edict_t *ed)
{
	gi.unlinkentity (ed);

	if ((ed - g_edicts) <= (maxclients->value + BODY_QUEUE_SIZE))
	{

		return;
	}

	memset (ed, 0, sizeof(*ed));
	ed->classname = "freed";
	ed->freetime = level.time;
	ed->inuse = false;
}
