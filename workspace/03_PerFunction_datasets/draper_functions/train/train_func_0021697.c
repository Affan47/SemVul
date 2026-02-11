gee_concurrent_set_tower_set_backlink (GeeConcurrentSetTower* self, GeeConcurrentSetTower* backlink, guint8 level) {
	GeeConcurrentSetTowerNode* _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	guint8 _tmp1_ = 0U;
	GeeConcurrentSetTower* _tmp2_ = NULL;
	GeeConcurrentSetTower* _tmp3_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->_nodes;
	_tmp0__length1 = -1;
	_tmp1_ = level;
	_tmp2_ = backlink;
	_tmp3_ = _gee_concurrent_set_tower_ref0 (_tmp2_);
	gee_hazard_pointer_compare_and_exchange_pointer (GEE_CONCURRENT_SET_TYPE_TOWER, (GBoxedCopyFunc) gee_concurrent_set_tower_ref, gee_concurrent_set_tower_unref, &_tmp0_[_tmp1_]._backlink, NULL, _tmp3_, (gsize) 0, (gsize) 0, (gsize) 0);
}
