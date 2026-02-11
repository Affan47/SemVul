friends_dispatcher_do_sync (FriendsDispatcher* self, const gchar* action, guint* account_id, const gchar* argument, GError** error) {
	gchar* result = NULL;
	Block1Data* _data1_;
	GMainLoop* _tmp0_;
	gchar* _tmp1_;
	gchar* _tmp2_;
	gchar* account_id_str;
	guint* _tmp3_;
	DispatcherInterface* _tmp6_;
	const gchar* _tmp7_;
	const gchar* _tmp8_;
	const gchar* _tmp9_;
	GMainLoop* _tmp10_;
	const gchar* _tmp11_;
	gchar* _tmp12_;
#line 94 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 94 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	g_return_val_if_fail (action != NULL, NULL);
#line 94 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	g_return_val_if_fail (argument != NULL, NULL);
#line 94 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_data1_ = g_slice_new0 (Block1Data);
#line 94 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_data1_->_ref_count_ = 1;
#line 94 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_data1_->self = g_object_ref (self);
#line 100 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp0_ = g_main_loop_new (NULL, FALSE);
#line 100 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_data1_->loop = _tmp0_;
#line 101 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp1_ = g_strdup ("");
#line 101 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_data1_->_result_ = _tmp1_;
#line 102 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp2_ = g_strdup ("");
#line 102 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	account_id_str = _tmp2_;
#line 103 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp3_ = account_id;
#line 103 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	if (_tmp3_ != NULL) {
#line 1652 "dispatcher.c"
		guint* _tmp4_;
		gchar* _tmp5_ = NULL;
#line 104 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
		_tmp4_ = account_id;
#line 104 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
		_tmp5_ = g_strdup_printf ("%u", *_tmp4_);
#line 104 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
		_g_free0 (account_id_str);
#line 104 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
		account_id_str = _tmp5_;
#line 1663 "dispatcher.c"
	}
#line 105 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp6_ = self->priv->service;
#line 105 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp7_ = action;
#line 105 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp8_ = account_id_str;
#line 105 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp9_ = argument;
#line 105 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	dispatcher_interface_Do (_tmp6_, _tmp7_, _tmp8_, _tmp9_, ___lambda2__gasync_ready_callback, block1_data_ref (_data1_));
#line 116 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp10_ = _data1_->loop;
#line 116 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	g_main_loop_run (_tmp10_);
#line 117 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp11_ = _data1_->_result_;
#line 117 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_tmp12_ = g_strdup (_tmp11_);
#line 117 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	result = _tmp12_;
#line 117 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_g_free0 (account_id_str);
#line 117 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	block1_data_unref (_data1_);
#line 117 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	_data1_ = NULL;
#line 117 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/src/dispatcher.vala"
	return result;
#line 1693 "dispatcher.c"
}
