gbemol_mpd_search_field_start (GbemolMpd* obj, gint field)
{
	if (!gbemol_mpd_is_connected (obj))
		return;

	mpd_startFieldSearch (obj->priv->conn, field);
}
