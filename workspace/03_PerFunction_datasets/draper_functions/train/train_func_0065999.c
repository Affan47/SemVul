PMenu_Close (edict_t * ent)
{
	if (!ent->client->menu)
		return;

	gi.TagFree (ent->client->menu);
	ent->client->menu = NULL;
	ent->client->showscores = false;
}
