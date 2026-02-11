fso_framework_test_test_case_construct (GType object_type, const gchar* name) {
	FsoFrameworkTestTestCase * self = NULL;
	const gchar* _tmp0_ = NULL;
	GTestSuite* _tmp1_ = NULL;
	g_return_val_if_fail (name != NULL, NULL);
	self = (FsoFrameworkTestTestCase*) g_object_new (object_type, NULL);
	_tmp0_ = name;
	_tmp1_ = g_test_create_suite (_tmp0_);
	self->priv->_suite = _tmp1_;
	return self;
}
