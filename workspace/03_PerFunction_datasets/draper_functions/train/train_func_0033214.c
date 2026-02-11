find_aot_module_cb (gpointer key, gpointer value, gpointer user_data)
{
	FindAotModuleUserData *data = (FindAotModuleUserData*)user_data;
	MonoAotModule *aot_module = (MonoAotModule*)value;

	if ((data->addr >= (guint8*)(aot_module->code)) && (data->addr < (guint8*)(aot_module->code_end)))
		data->module = aot_module;
}
