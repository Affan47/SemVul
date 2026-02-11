update_driving_value(
	struct driver *driver,
	universal_integer sim_time,
	const struct glue_vhdl_cb *callbacks
)
{
	struct drv_trans *t;

	if (driver->transactions->first == NULL) {
		return false;
	}

	t = (struct drv_trans *)driver->transactions->first->data;

	if (sim_time < t->sim_time) {

		return false;
	}


	driver->active = true;
	driver->driving_value = t->val;
	slset_remove(driver->transactions, t, callbacks->free);
	callbacks->free(t);
	return true;
}
