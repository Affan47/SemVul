cl_msg_mod(struct ha_msg * msg, const char * name,
	       const void* value, size_t vlen, int type)
{
  	int j;
	int rc;

	PARANOIDAUDITMSG(msg);
	if (msg == NULL || name == NULL || value == NULL) {
		cl_log(LOG_ERR, "cl_msg_mod: NULL input.");
		return HA_FAIL;
	}

	if(type >= DIMOF(fieldtypefuncs)){
		cl_log(LOG_ERR, "cl_msg_mod:"
		       "invalid type(%d)", type);
		return HA_FAIL;
	}

	for (j=0; j < msg->nfields; ++j) {
		if (strcmp(name, msg->names[j]) == 0) {

			char *	newv ;
			int	newlen = vlen;

			if (type != msg->types[j]){
				cl_log(LOG_ERR, "%s: type mismatch(%d %d)",
				       __FUNCTION__, type, msg->types[j]);
				return HA_FAIL;
			}

			newv = fieldtypefuncs[type].dup(value,vlen);
			if (!newv){
				cl_log(LOG_ERR, "duplicating message fields failed"
				       "value=%p, vlen=%d, msg->names[j]=%s",
				       value, (int)vlen, msg->names[j]);
				return HA_FAIL;
			}

			fieldtypefuncs[type].memfree(msg->values[j]);
			msg->values[j] = newv;
			msg->vlens[j] = newlen;
			PARANOIDAUDITMSG(msg);
			return(HA_OK);
		}
	}

	rc = ha_msg_nadd_type(msg, name,strlen(name), value, vlen, type);

	PARANOIDAUDITMSG(msg);
	return rc;
}
