dispatcher_suite_construct (GType object_type) {
	DispatcherSuite * self = NULL;
	FriendsDispatcher* _tmp0_;
	FriendsDispatcher* _tmp1_;
	GError * _inner_error_ = NULL;
#line 24 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	self = (DispatcherSuite*) g_object_new (object_type, NULL);
#line 26 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_tmp0_ = friends_dispatcher_new (&_inner_error_);
#line 26 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_tmp1_ = _tmp0_;
#line 26 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	if (_inner_error_ != NULL) {
#line 26 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 26 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
		g_clear_error (&_inner_error_);
#line 26 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
		return NULL;
#line 454 "test-dispatcher.c"
	}
#line 26 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	_g_object_unref0 (self->priv->dispatcher);
#line 26 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	self->priv->dispatcher = _tmp1_;
#line 29 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Refresh", self, _dispatcher_suite_test_refresh_gtest_data_func);
#line 32 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Features", self, _dispatcher_suite_test_features_gtest_data_func);
#line 35 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Upload", self, _dispatcher_suite_test_upload_gtest_data_func);
#line 42 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/SendMessageAccount", self, _dispatcher_suite_test_send_message_with_account_gtest_data_func);
#line 45 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/SendReply", self, _dispatcher_suite_test_send_reply_gtest_data_func);
#line 48 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Retweet", self, _dispatcher_suite_test_retweet_gtest_data_func);
#line 51 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Home", self, _dispatcher_suite_test_home_gtest_data_func);
#line 54 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Wall", self, _dispatcher_suite_test_wall_gtest_data_func);
#line 57 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Search", self, _dispatcher_suite_test_search_gtest_data_func);
#line 60 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Like", self, _dispatcher_suite_test_like_gtest_data_func);
#line 63 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Unlike", self, _dispatcher_suite_test_unlike_gtest_data_func);
#line 66 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Delete", self, _dispatcher_suite_test_delete_gtest_data_func);
#line 69 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/Contacts", self, _dispatcher_suite_test_contacts_gtest_data_func);
#line 77 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/URLShorten", self, _dispatcher_suite_test_url_shorten_gtest_data_func);
#line 82 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/UploadAsync", self, _dispatcher_suite_test_upload_async_gtest_data_func);
#line 85 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/SendMessageAsync", self, _dispatcher_suite_test_send_message_async_gtest_data_func);
#line 88 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/SendReplyAsync", self, _dispatcher_suite_test_send_reply_async_gtest_data_func);
#line 91 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/RetweetAsync", self, _dispatcher_suite_test_retweet_async_gtest_data_func);
#line 94 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/HomeAsync", self, _dispatcher_suite_test_home_async_gtest_data_func);
#line 97 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/WallAsync", self, _dispatcher_suite_test_wall_async_gtest_data_func);
#line 100 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/SearchAsync", self, _dispatcher_suite_test_search_async_gtest_data_func);
#line 103 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/LikeAsync", self, _dispatcher_suite_test_like_async_gtest_data_func);
#line 106 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/UnlikeAsync", self, _dispatcher_suite_test_unlike_async_gtest_data_func);
#line 109 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/DeleteAsync", self, _dispatcher_suite_test_delete_async_gtest_data_func);
#line 112 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	g_test_add_data_func ("/Unit/Friends/Dispatcher/ContactsAsync", self, _dispatcher_suite_test_contacts_async_gtest_data_func);
#line 24 "/tmp/buildd/libfriends-0.1.2+14.04.20131108.1/tests/vala/test-dispatcher.vala"
	return self;
#line 512 "test-dispatcher.c"
}
