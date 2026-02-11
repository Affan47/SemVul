_action_update_callback (MidgardObject *object, gpointer ud)
{
	MidgardMetadata *mdata = (MidgardMetadata *) ud;

	gchar *person_guid = "";
	MidgardConnection *mgd = MGD_OBJECT_CNC(object);
	MidgardObject *person = MGD_CNC_PERSON (mgd);

	if (person)
		person_guid = (gchar *)MGD_OBJECT_GUID(person);


	GValue rval = {0, };
	g_value_init (&rval, G_TYPE_STRING);
	g_value_set_string (&rval, person_guid);
	midgard_core_metadata_set_revisor (mdata, (const GValue *)&rval);
	g_value_unset (&rval);


	GValue tval = {0, };
	midgard_timestamp_new_current (&tval);
	midgard_core_metadata_set_revised (mdata, (const GValue *)&tval);
	g_value_unset (&tval);


	midgard_core_metadata_increase_revision (mdata);
}
