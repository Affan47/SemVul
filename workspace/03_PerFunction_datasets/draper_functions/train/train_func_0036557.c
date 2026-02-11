geoclue_nominatim_dispose (GObject *obj)
{
	GeoclueNominatim *self = (GeoclueNominatim *) obj;

	if (self->geocoder) {
		g_object_unref (self->geocoder);
		self->geocoder = NULL;
	}

	if (self->rev_geocoder) {
		g_object_unref (self->rev_geocoder);
		self->rev_geocoder = NULL;
	}

	((GObjectClass *) geoclue_nominatim_parent_class)->dispose (obj);
}
