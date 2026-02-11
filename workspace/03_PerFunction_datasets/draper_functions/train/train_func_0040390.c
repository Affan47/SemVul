low_level_openmoko_real_resume (FsoGsmLowLevel* base) {
	LowLevelOpenmoko * self;
	gboolean result = FALSE;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp2_ = NULL;
	self = (LowLevelOpenmoko*) base;
	_tmp0_ = self->priv->fcNode;
	if (g_strcmp0 (_tmp0_, "unknown") == 0) {
		FsoFrameworkLogger* _tmp1_ = NULL;
		_tmp1_ = ((FsoFrameworkAbstractObject*) self)->logger;
		fso_framework_logger_error (_tmp1_, "fc_node not defined. Can't recover from suspend.");
		result = FALSE;
		return result;
	}
	_tmp2_ = self->priv->fcNode;
	fso_framework_file_handling_write ("0", _tmp2_, FALSE);
	result = TRUE;
	return result;
}
