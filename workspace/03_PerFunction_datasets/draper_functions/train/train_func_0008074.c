position_changed_cb (GeocluePosition      *position,
		     GeocluePositionFields fields,
		     int                   timestamp,
		     double                latitude,
		     double                longitude,
		     double                altitude,
		     GeoclueAccuracy      *accuracy,
		     gpointer              userdata)
{
	GeoclueAccuracyLevel level;

	geoclue_accuracy_get_details (accuracy, &level, NULL, NULL);
	g_print ("New position (accuracy level %d):\n", level);

	if (fields & GEOCLUE_POSITION_FIELDS_LATITUDE &&
	    fields & GEOCLUE_POSITION_FIELDS_LONGITUDE) {
		g_print ("\t%f, %f\n\n", latitude, longitude);
	} else {
		g_print ("\nlatitude and longitude not valid.\n");
	}
}
