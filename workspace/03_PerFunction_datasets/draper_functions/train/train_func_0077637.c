gee_concurrent_set_tower_backtrace (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeConcurrentSetTower** curr, guint8 level) {
	while (TRUE) {
		GeeConcurrentSetTower* _tmp0_ = NULL;
		guint8 _tmp1_ = 0U;
		GeeConcurrentSetState _tmp2_ = 0;
		GeeConcurrentSetTower* _tmp3_ = NULL;
		guint8 _tmp4_ = 0U;
		GeeConcurrentSetTower* _tmp5_ = NULL;
		_tmp0_ = *curr;
		_tmp1_ = level;
		_tmp2_ = gee_concurrent_set_tower_get_state (_tmp0_, _tmp1_);
		if (!(_tmp2_ == GEE_CONCURRENT_SET_STATE_MARKED)) {
			break;
		}
		_tmp3_ = *curr;
		_tmp4_ = level;
		_tmp5_ = gee_concurrent_set_tower_get_backlink (_tmp3_, _tmp4_);
		_gee_concurrent_set_tower_unref0 (*curr);
		*curr = _tmp5_;
	}
}
