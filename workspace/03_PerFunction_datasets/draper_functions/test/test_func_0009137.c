gda_holder_set_attribute (GdaHolder *holder, const gchar *attribute, const GValue *value, GDestroyNotify destroy)
{
	const GValue *cvalue;
	g_return_if_fail (GDA_IS_HOLDER (holder));

	gda_holder_lock ((GdaLockable*) holder);
	cvalue = gda_attributes_manager_get (gda_holder_attributes_manager, holder, attribute);
	if ((value && cvalue && !gda_value_differ (cvalue, value)) ||
	    (!value && !cvalue)) {
		gda_holder_unlock ((GdaLockable*) holder);
		return;
	}

	gda_attributes_manager_set_full (gda_holder_attributes_manager, holder, attribute, value, destroy);

	gda_holder_unlock ((GdaLockable*) holder);
}
