_conf_parse_string(char **token, const char *name, char **value, char *saveptr)
{
	*token = strtok_r(NULL, " ", &saveptr);
	if(*token){
		if(*value){
			_mosquitto_log_printf(NULL, MOSQ_LOG_ERR, "Error: Duplicate %s value in configuration.", name);
			return MOSQ_ERR_INVAL;
		}
		*value = _mosquitto_strdup(*token);
		if(!*value){
			_mosquitto_log_printf(NULL, MOSQ_LOG_ERR, "Error: Out of memory");
			return MOSQ_ERR_NOMEM;
		}
	}else{
		_mosquitto_log_printf(NULL, MOSQ_LOG_ERR, "Error: Empty %s value in configuration.", name);
		return MOSQ_ERR_INVAL;
	}
	return MOSQ_ERR_SUCCESS;
}
