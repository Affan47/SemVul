gee_concurrent_set_tower_remove_level (GCompareDataFunc cmp, void* cmp_target, GeeConcurrentSetTower** prev, GeeConcurrentSetTower* curr, guint8 level) {
	gboolean result = FALSE;
	gboolean status = FALSE;
	gboolean flagged = FALSE;
	GeeConcurrentSetTower* _tmp0_ = NULL;
	GCompareDataFunc _tmp1_ = NULL;
	void* _tmp1__target = NULL;
	guint8 _tmp2_ = 0U;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp4_ = FALSE;
	gboolean _tmp5_ = FALSE;
	g_return_val_if_fail (*prev != NULL, FALSE);
	g_return_val_if_fail (curr != NULL, FALSE);
	_tmp0_ = curr;
	_tmp1_ = cmp;
	_tmp1__target = cmp_target;
	_tmp2_ = level;
	_tmp4_ = gee_concurrent_set_tower_try_flag (_tmp0_, _tmp1_, _tmp1__target, prev, &_tmp3_, _tmp2_);
	status = _tmp3_;
	flagged = _tmp4_;
	_tmp5_ = status;
	if (_tmp5_) {
		GeeConcurrentSetTower* _tmp6_ = NULL;
		GeeConcurrentSetTower* _tmp7_ = NULL;
		guint8 _tmp8_ = 0U;
		_tmp6_ = curr;
		_tmp7_ = *prev;
		_tmp8_ = level;
		gee_concurrent_set_tower_help_flagged (_tmp6_, _tmp7_, _tmp8_);
	}
	result = flagged;
	return result;
}
