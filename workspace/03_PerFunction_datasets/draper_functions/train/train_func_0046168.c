cb_instance_abandonto_set(void *arg, void *value, char *errorbuf, int phase, int apply)
{
	cb_backend_instance * inst=(cb_backend_instance *) arg;

	if (apply) {
		if (( phase != CB_CONFIG_PHASE_INITIALIZATION ) &&
    			( phase != CB_CONFIG_PHASE_STARTUP )) {


			return LDAP_SUCCESS;
		}

               	slapi_rwlock_wrlock(inst->rwl_config_lock);
		inst->abandon_timeout.tv_sec=(int) ((uintptr_t)value);
		inst->abandon_timeout.tv_usec=0;
               	slapi_rwlock_unlock(inst->rwl_config_lock);
	}
	return LDAP_SUCCESS;
}
