krb5_appdefault_boolean(krb5_context context, const char *appname,
			krb5_const_realm realm, const char *option,
			krb5_boolean def_val, krb5_boolean *ret_val)
{

    if(appname == NULL)
	appname = getprogname();

    def_val = krb5_config_get_bool_default(context, NULL, def_val,
					   "libdefaults", option, NULL);
    if(realm != NULL)
	def_val = krb5_config_get_bool_default(context, NULL, def_val,
					       "realms", realm, option, NULL);

    def_val = krb5_config_get_bool_default(context, NULL, def_val,
					   "appdefaults",
					   option,
					   NULL);
    if(realm != NULL)
	def_val = krb5_config_get_bool_default(context, NULL, def_val,
					       "appdefaults",
					       realm,
					       option,
					       NULL);
    if(appname != NULL) {
	def_val = krb5_config_get_bool_default(context, NULL, def_val,
					       "appdefaults",
					       appname,
					       option,
					       NULL);
	if(realm != NULL)
	    def_val = krb5_config_get_bool_default(context, NULL, def_val,
						   "appdefaults",
						   appname,
						   realm,
						   option,
						   NULL);
    }
    *ret_val = def_val;
}
