Device_property_get(Device *self,DevicePropertyBase *pbase,GValue *out_val,PropertySurety *surety,PropertySource *source,gboolean *val_found){
	    if (pbase) {
		*val_found = device_property_get_ex(self, pbase->ID, out_val, surety, source);
	    } else {
		*val_found = FALSE;
	    }
	}
