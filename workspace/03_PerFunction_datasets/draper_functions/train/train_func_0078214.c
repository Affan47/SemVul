uint_hash_static (UInt* that) {
	guint result = 0U;
	UInt* _tmp0_ = NULL;
	guint _tmp1_ = 0U;
#line 45 "/home/treitter/collabora/folks/tests/folks/small-set.vala"
	g_return_val_if_fail (that != NULL, 0U);
#line 47 "/home/treitter/collabora/folks/tests/folks/small-set.vala"
	_tmp0_ = that;
#line 47 "/home/treitter/collabora/folks/tests/folks/small-set.vala"
	_tmp1_ = _tmp0_->u;
#line 47 "/home/treitter/collabora/folks/tests/folks/small-set.vala"
	result = _tmp1_;
#line 47 "/home/treitter/collabora/folks/tests/folks/small-set.vala"
	return result;
#line 311 "small-set.c"
}
