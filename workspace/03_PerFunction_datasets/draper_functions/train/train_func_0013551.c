__lambda13_ (Block7Data* _data7_, GObject* o, GAsyncResult* r) {
	ObjectCacheTests * self;
	GAsyncResult* _tmp0_ = NULL;
#line 358 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	self = _data7_->self;
#line 358 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	g_return_if_fail (r != NULL);
#line 360 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	_tmp0_ = r;
#line 360 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	folks_object_cache_clear_cache_finish ((FolksObjectCache*) _data7_->cache, _tmp0_);
#line 361 "/home/treitter/collabora/folks/tests/folks/object-cache.vala"
	g_main_loop_quit (_data7_->main_loop);
#line 2485 "object-cache.c"
}
