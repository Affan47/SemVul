extractor_apply_geolocation_metadata (MetadataExtractor     *extractor,
                                      GstTagList            *tag_list,
                                      TrackerSparqlBuilder  *preupdate,
                                      TrackerSparqlBuilder  *metadata,
                                      const gchar           *graph)
{
	gchar *country = NULL, *city = NULL, *sublocation = NULL;
	gdouble lat, lon, alt;
	gboolean has_coords;

	g_debug ("Retrieving geolocation metadata...");

	country = city = sublocation = NULL;
	has_coords = (gst_tag_list_get_double (tag_list, GST_TAG_GEO_LOCATION_LATITUDE, &lat) &&
	              gst_tag_list_get_double (tag_list, GST_TAG_GEO_LOCATION_LONGITUDE, &lon) &&
	              gst_tag_list_get_double (tag_list, GST_TAG_GEO_LOCATION_ELEVATION, &alt));

	gst_tag_list_get_string (tag_list, GST_TAG_GEO_LOCATION_CITY, &city);
	gst_tag_list_get_string (tag_list, GST_TAG_GEO_LOCATION_COUNTRY, &country);
	gst_tag_list_get_string (tag_list, GST_TAG_GEO_LOCATION_SUBLOCATION, &sublocation);

	if (city || country || sublocation || has_coords) {
		gchar *address_uri = NULL;


		if (city || country || sublocation) {
			address_uri = tracker_sparql_get_uuid_urn ();

			tracker_sparql_builder_insert_open (preupdate, NULL);
			if (graph) {
				tracker_sparql_builder_graph_open (preupdate, graph);
			}

			tracker_sparql_builder_subject_iri (preupdate, address_uri);
			tracker_sparql_builder_predicate (preupdate, "a");
			tracker_sparql_builder_object (preupdate, "nco:PostalAddress");

			if (sublocation) {
				tracker_sparql_builder_predicate (preupdate, "nco:region");
				tracker_sparql_builder_object_unvalidated (preupdate, sublocation);
			}

			if (city) {
				tracker_sparql_builder_predicate (preupdate, "nco:locality");
				tracker_sparql_builder_object_unvalidated (preupdate, city);
			}

			if (country) {
				tracker_sparql_builder_predicate (preupdate, "nco:country");
				tracker_sparql_builder_object_unvalidated (preupdate, country);
			}

			if (graph) {
				tracker_sparql_builder_graph_close (preupdate);
			}
			tracker_sparql_builder_insert_close (preupdate);
		}


		tracker_sparql_builder_predicate (metadata, "slo:location");

		tracker_sparql_builder_object_blank_open (metadata);
		tracker_sparql_builder_predicate (metadata, "a");
		tracker_sparql_builder_object (metadata, "slo:GeoLocation");

		if (address_uri) {
			tracker_sparql_builder_predicate (metadata, "slo:postalAddress");
			tracker_sparql_builder_object_iri (metadata, address_uri);
		}

		if (has_coords) {
			tracker_sparql_builder_predicate (metadata, "slo:latitude");
			tracker_sparql_builder_object_double (metadata, lat);

			tracker_sparql_builder_predicate (metadata, "slo:longitude");
			tracker_sparql_builder_object_double (metadata, lon);

			tracker_sparql_builder_predicate (metadata, "slo:altitude");
			tracker_sparql_builder_object_double (metadata, alt);
		}

		tracker_sparql_builder_object_blank_close (metadata);
		g_free (address_uri);
	}

	g_free (city);
	g_free (country);
	g_free (sublocation);
}
