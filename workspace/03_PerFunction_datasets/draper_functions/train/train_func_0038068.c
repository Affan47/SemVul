dispatcher_suite_test_send_message_async (DispatcherSuite* self) {
	Block2Data* _data2_;
	GMainLoop* _tmp0_;
	gchar* _tmp1_;
	FriendsDispatcher* _tmp2_;
	guint _tmp3_;
#line 170 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_return_if_fail (self != NULL);
#line 170 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_data2_ = g_slice_new0 (Block2Data);
#line 170 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_data2_->_ref_count_ = 1;
#line 170 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_data2_->self = g_object_ref (self);
#line 172 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_tmp0_ = g_main_loop_new (NULL, FALSE);
#line 172 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_data2_->loop = _tmp0_;
#line 173 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_tmp1_ = g_strdup ("");
#line 173 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_data2_->_result_ = _tmp1_;
#line 174 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_tmp2_ = self->priv->dispatcher;
#line 174 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_tmp3_ = (guint) 3;
#line 174 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	friends_dispatcher_send_message_async (_tmp2_, &_tmp3_, "Goodbye", ___lambda3__gasync_ready_callback, block2_data_ref (_data2_));
#line 180 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_main_loop_run (_data2_->loop);
#line 182 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_vala_assert (g_strcmp0 (_data2_->_result_, "Called with: action=send, account_id=3, arg=Goodbye") == 0, "result == \"Called with: action=send, account_id=3, arg=Goodbye\"");
#line 170 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	block2_data_unref (_data2_);
#line 170 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_data2_ = NULL;
#line 929 "test-dispatcher.c"
}
