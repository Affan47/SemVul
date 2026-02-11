cb_instance_bindmech_set(void *arg, void *value, char *errorbuf, int phase, int apply)
{
	cb_backend_instance * inst=(cb_backend_instance *) arg;
	int rc=LDAP_SUCCESS;

	if (!inst) {
		PR_snprintf (errorbuf, SLAPI_DSE_RETURNTEXT_SIZE, "NULL instance");
		rc = LDAP_OPERATIONS_ERROR;
		goto done;
	}

	if (value && !PL_strcasecmp((char *) value, "GSSAPI") && inst->rwl_config_lock) {
		int secure = 0;
		slapi_rwlock_rdlock(inst->rwl_config_lock);
		secure = inst->pool->secure || inst->pool->starttls;
		slapi_rwlock_unlock(inst->rwl_config_lock);
		if (secure) {
			PR_snprintf (errorbuf, SLAPI_DSE_RETURNTEXT_SIZE, "Cannot use SASL/GSSAPI if using SSL or TLS - please change the connection to use no security before changing %s to use GSSAPI", CB_CONFIG_BINDMECH);
			rc = LDAP_UNWILLING_TO_PERFORM;
		}
	}

	if ((LDAP_SUCCESS == rc) && apply) {
               	slapi_rwlock_wrlock(inst->rwl_config_lock);
		if (( phase != CB_CONFIG_PHASE_INITIALIZATION ) &&
    			( phase != CB_CONFIG_PHASE_STARTUP )) {


			if (inst->pool->mech) {
			    charray_add(&inst->pool->waste_basket,inst->pool->mech);
			}
			if (inst->bind_pool->mech) {
			    charray_add(&inst->bind_pool->waste_basket,inst->bind_pool->mech);
			}
			rc=CB_REOPEN_CONN;
		}

		if (value && !PL_strcasecmp((char *) value, CB_SIMPLE_BINDMECH)) {
		    inst->pool->mech=slapi_ch_strdup(LDAP_SASL_SIMPLE);
		} else {
		    inst->pool->mech=slapi_ch_strdup((char *) value);
		}
		inst->bind_pool->mech = slapi_ch_strdup(inst->pool->mech);
               	slapi_rwlock_unlock(inst->rwl_config_lock);
	}
done:
	return rc;
}
