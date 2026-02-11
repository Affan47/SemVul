folks_abstract_field_details_equal_static (FolksAbstractFieldDetails* left, FolksAbstractFieldDetails* right) {
	gboolean result = FALSE;
	FolksAbstractFieldDetails* _tmp0_ = NULL;
	FolksAbstractFieldDetails* _tmp1_ = NULL;
	FolksAbstractFieldDetails* left_details = NULL;
	FolksAbstractFieldDetails* _tmp2_ = NULL;
	FolksAbstractFieldDetails* _tmp3_ = NULL;
	FolksAbstractFieldDetails* right_details = NULL;
	FolksAbstractFieldDetails* _tmp4_ = NULL;
	FolksAbstractFieldDetails* _tmp5_ = NULL;
	gboolean _tmp6_ = FALSE;
	g_return_val_if_fail (left != NULL, FALSE);
	g_return_val_if_fail (right != NULL, FALSE);
	_tmp0_ = left;
	g_return_val_if_fail (_tmp0_ != NULL, FALSE);
	_tmp1_ = right;
	g_return_val_if_fail (_tmp1_ != NULL, FALSE);
	_tmp2_ = left;
	_tmp3_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp2_, FOLKS_TYPE_ABSTRACT_FIELD_DETAILS, FolksAbstractFieldDetails));
	left_details = _tmp3_;
	_tmp4_ = right;
	_tmp5_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp4_, FOLKS_TYPE_ABSTRACT_FIELD_DETAILS, FolksAbstractFieldDetails));
	right_details = _tmp5_;
	_tmp6_ = folks_abstract_field_details_equal (left_details, right_details);
	result = _tmp6_;
	_g_object_unref0 (right_details);
	_g_object_unref0 (left_details);
	return result;
}
