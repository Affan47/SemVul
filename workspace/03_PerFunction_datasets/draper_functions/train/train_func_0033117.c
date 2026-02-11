gdata_gcontact_event_set_date (GDataGContactEvent *self, const GDate *date)
{
	g_return_if_fail (GDATA_IS_GCONTACT_EVENT (self));
	g_return_if_fail (date != NULL && g_date_valid (date) == TRUE);

	self->priv->date = *date;
	g_object_notify (G_OBJECT (self), "date");
}
