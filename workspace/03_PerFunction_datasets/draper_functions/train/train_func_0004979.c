Cmd_VidRef_f (edict_t * ent)
{
	if (video_check->value || video_check_lockpvs->value)
	{
		Q_strncpyz (ent->client->resp.vidref, gi.argv(1), sizeof(ent->client->resp.vidref));
	}

}
