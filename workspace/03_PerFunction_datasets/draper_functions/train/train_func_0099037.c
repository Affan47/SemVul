gee_hazard_pointer_set_release_policy (GeeHazardPointerReleasePolicy policy) {
	gboolean result = FALSE;
	gint old_policy = 0;
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	GeeHazardPointerReleasePolicy _tmp3_ = 0;
	gboolean _tmp4_ = FALSE;
	_tmp0_ = g_atomic_int_get ((volatile gint *) (&gee_hazard_pointer_release_policy));
	old_policy = _tmp0_;
	_tmp1_ = old_policy;
	if ((_tmp1_ & ((sizeof (gint) * 8) - 1)) != 0) {
		g_critical ("hazardpointer.vala:276: Attempt to change the policy of running helper" \
". Failing.");
		result = FALSE;
		return result;
	}
	_tmp2_ = old_policy;
	_tmp3_ = policy;
	_tmp4_ = g_atomic_int_compare_and_exchange ((volatile gint *) (&gee_hazard_pointer_release_policy), _tmp2_, (gint) _tmp3_);
	if (!_tmp4_) {
		g_critical ("hazardpointer.vala:280: Concurrent access to release policy detected. " \
"Failing.");
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}
