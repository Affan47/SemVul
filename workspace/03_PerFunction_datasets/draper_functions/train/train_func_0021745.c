gmpc_provider_render_cover_real_get_metadata (GmpcPluginMetaDataIface* base, mpd_Song* song, MetaDataType type, GmpcPluginMetaDataCallback callback, void* callback_target) {
	GmpcProviderRenderCover * self;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	mpd_Song* _tmp2_;
	gboolean _tmp5_;
	gboolean _tmp8_;
	MetaDataType _tmp10_;
	GmpcPluginMetaDataCallback _tmp13_;
	void* _tmp13__target;
	self = (GmpcProviderRenderCover*) base;
	_tmp2_ = song;
	if (_tmp2_ == NULL) {
		_tmp1_ = TRUE;
	} else {
		mpd_Song* _tmp3_;
		const gchar* _tmp4_;
		_tmp3_ = song;
		_tmp4_ = _tmp3_->artist;
		_tmp1_ = _tmp4_ == NULL;
	}
	_tmp5_ = _tmp1_;
	if (_tmp5_) {
		_tmp0_ = TRUE;
	} else {
		mpd_Song* _tmp6_;
		const gchar* _tmp7_;
		_tmp6_ = song;
		_tmp7_ = _tmp6_->album;
		_tmp0_ = _tmp7_ == NULL;
	}
	_tmp8_ = _tmp0_;
	if (_tmp8_) {
		GmpcPluginMetaDataCallback _tmp9_;
		void* _tmp9__target;
		g_log (log_domain_prc, G_LOG_LEVEL_DEBUG, "RenderCover.vala:64: Insufficient information. doing nothing");
		_tmp9_ = callback;
		_tmp9__target = callback_target;
		_tmp9_ (NULL, _tmp9__target);
		return;
	}
	_tmp10_ = type;
	switch (_tmp10_) {
		case META_ALBUM_ART:
		{
			mpd_Song* _tmp11_;
			GmpcPluginMetaDataCallback _tmp12_;
			void* _tmp12__target;
			_tmp11_ = song;
			_tmp12_ = callback;
			_tmp12__target = callback_target;
			gmpc_provider_render_cover_get_album_art (self, _tmp11_, _tmp12_, _tmp12__target);
			return;
		}
		default:
		case META_ARTIST_TXT:
		case META_ARTIST_SIMILAR:
		case META_ARTIST_ART:
		case META_ALBUM_TXT:
		case META_SONG_TXT:
		case META_SONG_SIMILAR:
		case META_GENRE_SIMILAR:
		case META_SONG_GUITAR_TAB:
		case META_QUERY_DATA_TYPES:
		case META_QUERY_NO_CACHE:
		{
			break;
		}
	}
	_tmp13_ = callback;
	_tmp13__target = callback_target;
	_tmp13_ (NULL, _tmp13__target);
}
