fso_gsm_service_manager_registerService (FsoGsmServiceManager* self, GType t_type, GBoxedCopyFunc t_dup_func, GDestroyNotify t_destroy_func, FsoGsmService* serviceObject) {
	GHashTable* _tmp0_ = NULL;
	FsoGsmService* _tmp1_ = NULL;
	FsoGsmService* _tmp2_ = NULL;
	FsoFrameworkSubsystem* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	FsoGsmService* _tmp6_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (serviceObject != NULL);
	_tmp0_ = self->priv->services;
	_tmp1_ = serviceObject;
	_tmp2_ = _g_object_ref0 (_tmp1_);
	g_hash_table_insert (_tmp0_, (gpointer) ((gintptr) t_type), _tmp2_);
	_tmp3_ = self->priv->subsystem;
	_tmp4_ = self->priv->serviceName;
	_tmp5_ = self->priv->servicePath;
	_tmp6_ = serviceObject;
	fso_framework_subsystem_registerObjectForService (_tmp3_, t_type, (GBoxedCopyFunc) t_dup_func, t_destroy_func, _tmp4_, _tmp5_, _tmp6_);
}
