get_geocode_accuracy (GcWebService *geocoder)
{
	char *str;
	GeoclueAccuracyLevel level = GEOCLUE_ACCURACY_LEVEL_NONE;

	if (gc_web_service_get_string (geocoder, &str, NOMINATIM_LATLON_HOUSE)) {
		level = GEOCLUE_ACCURACY_LEVEL_DETAILED;
	} else if (gc_web_service_get_string (geocoder, &str,
	                                      NOMINATIM_LATLON_ROAD)) {
		level = GEOCLUE_ACCURACY_LEVEL_STREET;
	} else if (gc_web_service_get_string (geocoder, &str,
	                                      NOMINATIM_LATLON_SUBURB) ||
	           gc_web_service_get_string (geocoder, &str,
	                                      NOMINATIM_LATLON_POSTCODE) ||
	           gc_web_service_get_string (geocoder, &str,
	                                      NOMINATIM_LATLON_VILLAGE)) {
		level = GEOCLUE_ACCURACY_LEVEL_POSTALCODE;
	} else if (gc_web_service_get_string (geocoder, &str,
	                                      NOMINATIM_LATLON_CITY)) {
		level = GEOCLUE_ACCURACY_LEVEL_LOCALITY;
	} else if (gc_web_service_get_string (geocoder, &str,
	                                      NOMINATIM_LATLON_COUNTY)) {
		level = GEOCLUE_ACCURACY_LEVEL_REGION;
	} else if (gc_web_service_get_string (geocoder, &str,
	                                      NOMINATIM_LATLON_COUNTRY) ||
	           gc_web_service_get_string (geocoder, &str,
	                                      NOMINATIM_LATLON_COUNTRYCODE)) {
		level = GEOCLUE_ACCURACY_LEVEL_COUNTRY;
	}

	return geoclue_accuracy_new (level, 0, 0);
}
