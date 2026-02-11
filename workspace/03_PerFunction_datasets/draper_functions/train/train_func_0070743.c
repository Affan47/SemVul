mpd_stats_feed(struct mpd_stats *stats, const struct mpd_pair *pair)
{
	if (strcmp(pair->name, "artists") == 0)
		stats->number_of_artists = atoi(pair->value);
	else if (strcmp(pair->name, "albums") == 0)
		stats->number_of_albums = atoi(pair->value);
	else if (strcmp(pair->name, "songs") == 0)
		stats->number_of_songs = atoi(pair->value);
	else if (strcmp(pair->name, "uptime") == 0)
		stats->uptime = strtol(pair->value,NULL,10);
	else if (strcmp(pair->name, "db_update") == 0)
		stats->db_update_time = strtol(pair->value,NULL,10);
	else if (strcmp(pair->name, "playtime") == 0)
		stats->play_time = strtol(pair->value,NULL,10);
	else if (strcmp(pair->name, "db_playtime") == 0)
		stats->db_play_time = strtol(pair->value,NULL,10);
}
