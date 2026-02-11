http_impl_init(Slapi_ComponentId *plugin_id)
{
	int status = HTTP_IMPL_SUCCESS;
       	slapi_log_error(SLAPI_LOG_PLUGIN, HTTP_PLUGIN_SUBSYSTEM,
		"-> http_impl_init \n");
	httpConfig = NULL;

   	httpConfig = (httpPluginConfig *) slapi_ch_calloc(1, sizeof(httpPluginConfig));

	status = readConfigLDAPurl(plugin_id, HTTP_PLUGIN_DN);
    if (status != 0) {
       		 slapi_log_error(SLAPI_LOG_FATAL, HTTP_PLUGIN_SUBSYSTEM,
                        "http_impl_start: Unable to get HTTP config information \n");
        	 return HTTP_IMPL_FAILURE;
   	}

	status = readConfigLDAPurl(plugin_id, CONFIG_DN);
    if (status != 0) {
       		 slapi_log_error(SLAPI_LOG_FATAL, HTTP_PLUGIN_SUBSYSTEM,
                        "http_impl_start: Unable to get config information \n");
        	 return HTTP_IMPL_FAILURE;
    }

       	slapi_log_error(SLAPI_LOG_PLUGIN, HTTP_PLUGIN_SUBSYSTEM,
		"<- http_impl_init \n");

	return status;

}
