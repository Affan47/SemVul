xml_text_handler_metadata (GMarkupParseContext  *context,
                           const gchar          *text,
                           gsize                 text_len,
                           gpointer              user_data,
                           GError              **error)
{
	ODTMetadataParseInfo *data;
	TrackerSparqlBuilder *metadata;
	gchar *date;

	data = user_data;
	metadata = data->metadata;

	if (text_len == 0) {

		return;
	}

	switch (data->current) {
	case ODT_TAG_TYPE_TITLE:
		if (data->title_already_set) {
			g_warning ("Avoiding additional title (%s) in OASIS document '%s'",
			           text, data->uri);
		} else {
			data->title_already_set = TRUE;
			tracker_sparql_builder_predicate (metadata, "nie:title");
			tracker_sparql_builder_object_unvalidated (metadata, text);
		}
		break;

	case ODT_TAG_TYPE_SUBJECT:
		tracker_sparql_builder_predicate (metadata, "nie:subject");
		tracker_sparql_builder_object_unvalidated (metadata, text);
		break;

	case ODT_TAG_TYPE_AUTHOR:
		tracker_sparql_builder_predicate (metadata, "nco:publisher");

		tracker_sparql_builder_object_blank_open (metadata);
		tracker_sparql_builder_predicate (metadata, "a");
		tracker_sparql_builder_object (metadata, "nco:Contact");

		tracker_sparql_builder_predicate (metadata, "nco:fullname");
		tracker_sparql_builder_object_unvalidated (metadata, text);
		tracker_sparql_builder_object_blank_close (metadata);
		break;

	case ODT_TAG_TYPE_KEYWORDS: {
		gchar *keywords;
		gchar *lasts, *keyw;

		keywords = g_strdup (text);

		for (keyw = strtok_r (keywords, ",; ", &lasts);
		     keyw;
		     keyw = strtok_r (NULL, ",; ", &lasts)) {
			tracker_sparql_builder_predicate (metadata, "nie:keyword");
			tracker_sparql_builder_object_unvalidated (metadata, keyw);
		}

		g_free (keywords);

		break;
	}

	case ODT_TAG_TYPE_COMMENTS:
		tracker_sparql_builder_predicate (metadata, "nie:comment");
		tracker_sparql_builder_object_unvalidated (metadata, text);
		break;

	case ODT_TAG_TYPE_CREATED:
		date = tracker_date_guess (text);
		if (date) {
			tracker_sparql_builder_predicate (metadata, "nie:contentCreated");
			tracker_sparql_builder_object_unvalidated (metadata, date);
			g_free (date);
		}
		break;

	case ODT_TAG_TYPE_GENERATOR:
		tracker_sparql_builder_predicate (metadata, "nie:generator");
		tracker_sparql_builder_object_unvalidated (metadata, text);
		break;

	default:
	case ODT_TAG_TYPE_STATS:
		break;
	}
}
