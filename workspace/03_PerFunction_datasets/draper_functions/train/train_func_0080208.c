_friends_gtk_account_target_bar___lambda9_ (FriendsGtkAccountTargetBar* self, FriendsAccount* source) {
	GeeHashMap* _tmp0_;
	FriendsAccount* _tmp1_;
#line 489 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/gtk/entry.vala"
	g_return_if_fail (source != NULL);
#line 490 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/gtk/entry.vala"
	_tmp0_ = self->priv->accounts_buttons_map;
#line 490 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/gtk/entry.vala"
	_tmp1_ = source;
#line 490 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/gtk/entry.vala"
	friends_gtk_account_target_bar_account_created (self, _tmp0_, _tmp1_);
#line 3212 "entry.c"
}
