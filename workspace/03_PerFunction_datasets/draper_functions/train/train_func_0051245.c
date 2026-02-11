midgard_object_approve(MidgardObject *self)
{
	g_assert(self != NULL);
	g_object_ref(self);

	g_signal_emit(self, MIDGARD_OBJECT_GET_CLASS(self)->signal_action_approve, 0);

	MidgardConnection *mgd = MGD_OBJECT_CNC(self);
	MIDGARD_ERRNO_SET(mgd, MGD_ERR_OK);

	MidgardMetadata *metadata = MGD_DBOBJECT_METADATA (self);

	MidgardUser *user = midgard_connection_get_user(mgd);

	if (!user) {

		MIDGARD_ERRNO_SET(mgd, MGD_ERR_ACCESS_DENIED);
		g_object_unref(self);
		return FALSE;
	}

	const MidgardObject *person = midgard_user_get_person(user);

	if (!person) {

		MIDGARD_ERRNO_SET(mgd, MGD_ERR_INTERNAL);
		g_object_unref(self);
		return FALSE;
	}

	if (midgard_object_is_approved(self)) {

		g_warning("Object is already approved");
		return FALSE;
	}


	GValue tval = {0, };
	midgard_timestamp_new_current (&tval);


	GValue gval = {0, };
	g_value_init(&gval, G_TYPE_STRING);
	g_value_set_string(&gval, MGD_OBJECT_GUID(person));


	GValue aval = {0, };
	g_value_init(&aval, G_TYPE_BOOLEAN);
	g_value_set_boolean(&aval, TRUE);


	GValue rval = {0, };
	g_value_init(&rval, G_TYPE_UINT);
	g_value_set_uint(&rval, metadata->priv->revision+1);


	GValue stval = {0, };
	g_value_init (&stval, GDA_TYPE_TIMESTAMP);
	g_value_transform (&tval, &stval);

	gboolean rv = midgard_core_query_update_object_fields(
			MIDGARD_DBOBJECT(self),
			"metadata_approved", &stval,
			"metadata_approver", &gval,
			"metadata_isapproved", &aval,
			"metadata_revisor", &gval,
			"metadata_revised", &stval,
			"metadata_revision", &rval,
			NULL);


	if (rv) {

		metadata->priv->approve_is_set = TRUE;
		metadata->priv->is_approved = TRUE;

		midgard_core_metadata_set_approved (metadata, &tval);
		midgard_core_metadata_set_approver (metadata, &gval);
		midgard_core_metadata_set_revisor (metadata, &gval);
		midgard_core_metadata_set_revised (metadata, &tval);
		midgard_core_metadata_set_revision (metadata, &rval);
	}

	g_value_unset (&tval);
	g_value_unset (&stval);
	g_value_unset (&gval);
	g_value_unset (&aval);
	g_value_unset (&rval);

	g_object_unref(self);
	g_signal_emit(self, MIDGARD_OBJECT_GET_CLASS(self)->signal_action_approved, 0);

	return rv;
}
