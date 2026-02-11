gee_concurrent_set_tower_get_backlink (GeeConcurrentSetTower* self, guint8 level) {
	GeeConcurrentSetTower* result = NULL;
	GeeConcurrentSetTowerNode* _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	guint8 _tmp1_ = 0U;
	gpointer _tmp2_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->_nodes;
	_tmp0__length1 = -1;
	_tmp1_ = level;
	_tmp2_ = gee_hazard_pointer_get_pointer (GEE_CONCURRENT_SET_TYPE_TOWER, (GBoxedCopyFunc) gee_concurrent_set_tower_ref, gee_concurrent_set_tower_unref, &_tmp0_[_tmp1_]._backlink, (gsize) 0, NULL);
	result = (GeeConcurrentSetTower*) _tmp2_;
	return result;
}
