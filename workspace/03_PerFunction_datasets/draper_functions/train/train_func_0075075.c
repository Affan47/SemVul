skk_proxy_candidate_list_set_candidates (SkkProxyCandidateList* self, SkkCandidateList* value) {
	SkkCandidateList* _tmp0_;
	SkkCandidateList* _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_candidates;
	_tmp1_ = value;
	if (_tmp0_ != _tmp1_) {
		SkkCandidateList* _tmp2_;
		SkkCandidateList* _tmp10_;
		SkkCandidateList* _tmp11_;
		SkkCandidateList* _tmp12_;
		SkkCandidateList* _tmp13_;
		SkkCandidateList* _tmp14_;
		_tmp2_ = self->priv->_candidates;
		if (_tmp2_ != NULL) {
			SkkCandidateList* _tmp3_;
			guint _tmp4_ = 0U;
			GQuark _tmp5_ = 0U;
			SkkCandidateList* _tmp6_;
			guint _tmp7_ = 0U;
			SkkCandidateList* _tmp8_;
			guint _tmp9_ = 0U;
			_tmp3_ = self->priv->_candidates;
			g_signal_parse_name ("notify::cursor-pos", G_TYPE_OBJECT, &_tmp4_, &_tmp5_, TRUE);
			g_signal_handlers_disconnect_matched ((GObject*) _tmp3_, G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_DETAIL | G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA, _tmp4_, _tmp5_, NULL, (GCallback) _skk_proxy_candidate_list_notify_cursor_pos_cb_g_object_notify, self);
			_tmp6_ = self->priv->_candidates;
			g_signal_parse_name ("populated", SKK_TYPE_CANDIDATE_LIST, &_tmp7_, NULL, FALSE);
			g_signal_handlers_disconnect_matched (_tmp6_, G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA, _tmp7_, 0, NULL, (GCallback) _skk_proxy_candidate_list_populated_cb_skk_candidate_list_populated, self);
			_tmp8_ = self->priv->_candidates;
			g_signal_parse_name ("selected", SKK_TYPE_CANDIDATE_LIST, &_tmp9_, NULL, FALSE);
			g_signal_handlers_disconnect_matched (_tmp8_, G_SIGNAL_MATCH_ID | G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA, _tmp9_, 0, NULL, (GCallback) _skk_proxy_candidate_list_selected_cb_skk_candidate_list_selected, self);
		}
		_tmp10_ = value;
		_tmp11_ = _g_object_ref0 (_tmp10_);
		_g_object_unref0 (self->priv->_candidates);
		self->priv->_candidates = _tmp11_;
		_tmp12_ = self->priv->_candidates;
		g_signal_connect_object ((GObject*) _tmp12_, "notify::cursor-pos", (GCallback) _skk_proxy_candidate_list_notify_cursor_pos_cb_g_object_notify, self, 0);
		_tmp13_ = self->priv->_candidates;
		g_signal_connect_object (_tmp13_, "populated", (GCallback) _skk_proxy_candidate_list_populated_cb_skk_candidate_list_populated, self, 0);
		_tmp14_ = self->priv->_candidates;
		g_signal_connect_object (_tmp14_, "selected", (GCallback) _skk_proxy_candidate_list_selected_cb_skk_candidate_list_selected, self, 0);
		g_signal_emit_by_name ((SkkCandidateList*) self, "populated");
	}
	g_object_notify ((GObject *) self, "candidates");
}
