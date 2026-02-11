midgard_user_set_person (MidgardUser *self, MidgardObject *person)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (person != NULL, FALSE);

	GType person_type = g_type_from_name ("midgard_person");
	g_return_val_if_fail (MIDGARD_IS_OBJECT (person), FALSE);
	g_return_val_if_fail (person_type == G_OBJECT_TYPE (person), FALSE);

	g_return_val_if_fail (MGD_OBJECT_GUID (person) != NULL, FALSE);

	if (G_IS_OBJECT (self->priv->person))
		g_object_unref (self->priv->person);
	self->priv->person = g_object_ref (person);
	g_free (self->priv->person_guid);
	self->priv->person_guid = g_strdup (MGD_OBJECT_GUID (person));

	return midgard_user_update (self);
}
