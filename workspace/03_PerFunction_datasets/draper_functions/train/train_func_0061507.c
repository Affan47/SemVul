unity_track_metadata_construct_full (GType object_type, const gchar* uri, gint track_no, const gchar* title, const gchar* artist, const gchar* album, guint length) {
	UnityTrackMetadata * self = NULL;
	const gchar* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	guint _tmp5_ = 0U;
	g_return_val_if_fail (uri != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	g_return_val_if_fail (artist != NULL, NULL);
	g_return_val_if_fail (album != NULL, NULL);
	_tmp0_ = uri;
	_tmp1_ = track_no;
	_tmp2_ = title;
	_tmp3_ = artist;
	_tmp4_ = album;
	_tmp5_ = length;
	self = (UnityTrackMetadata*) g_object_new (object_type, "uri", _tmp0_, "track-no", _tmp1_, "title", _tmp2_, "artist", _tmp3_, "album", _tmp4_, "length", _tmp5_, NULL);
	return self;
}
