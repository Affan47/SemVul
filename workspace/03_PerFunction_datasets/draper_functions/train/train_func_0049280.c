msoffice_xml_metadata_parse (GMarkupParseContext  *context,
                             const gchar          *text,
                             gsize                 text_len,
                             gpointer              user_data,
                             GError              **error)
{
	MsOfficeXMLParserInfo *info = user_data;

	switch (info->tag_type) {

	case MS_OFFICE_XML_TAG_WORD_TEXT:
	case MS_OFFICE_XML_TAG_SLIDE_TEXT:
	case MS_OFFICE_XML_TAG_XLS_SHARED_TEXT:
		break;

	case MS_OFFICE_XML_TAG_TITLE:
		if (info->title_already_set) {
			g_warning ("Avoiding additional title (%s) in MsOffice XML document '%s'",
			           text, info->uri);
		} else {
			info->title_already_set = TRUE;
			tracker_sparql_builder_predicate (info->metadata, "nie:title");
			tracker_sparql_builder_object_unvalidated (info->metadata, text);
		}
		break;

	case MS_OFFICE_XML_TAG_SUBJECT:
		tracker_sparql_builder_predicate (info->metadata, "nie:subject");
		tracker_sparql_builder_object_unvalidated (info->metadata, text);
		break;

	case MS_OFFICE_XML_TAG_AUTHOR:
		tracker_sparql_builder_predicate (info->metadata, "nco:publisher");

		tracker_sparql_builder_object_blank_open (info->metadata);
		tracker_sparql_builder_predicate (info->metadata, "a");
		tracker_sparql_builder_object (info->metadata, "nco:Contact");

		tracker_sparql_builder_predicate (info->metadata, "nco:fullname");
		tracker_sparql_builder_object_unvalidated (info->metadata, text);
		tracker_sparql_builder_object_blank_close (info->metadata);
		break;

	case MS_OFFICE_XML_TAG_COMMENTS:
		tracker_sparql_builder_predicate (info->metadata, "nie:comment");
		tracker_sparql_builder_object_unvalidated (info->metadata, text);
		break;

	case MS_OFFICE_XML_TAG_CREATED: {
		gchar *date;

		date = tracker_date_guess (text);
		tracker_sparql_builder_predicate (info->metadata, "nie:contentCreated");
		tracker_sparql_builder_object_unvalidated (info->metadata, date);
		g_free (date);
		break;
	}

	case MS_OFFICE_XML_TAG_GENERATOR:
		if (info->generator_already_set) {
			g_warning ("Avoiding additional generator (%s) in MsOffice XML document '%s'",
			           text, info->uri);
		} else {
			info->generator_already_set = TRUE;
			tracker_sparql_builder_predicate (info->metadata, "nie:generator");
			tracker_sparql_builder_object_unvalidated (info->metadata, text);
		}
		break;

	case MS_OFFICE_XML_TAG_APPLICATION:


		break;

	case MS_OFFICE_XML_TAG_MODIFIED: {
		gchar *date;

                date = tracker_date_guess (text);
		tracker_sparql_builder_predicate (info->metadata, "nie:contentLastModified");
		tracker_sparql_builder_object_unvalidated (info->metadata, date);
                g_free (date);
		break;
	}

	case MS_OFFICE_XML_TAG_NUM_OF_PAGES:
		tracker_sparql_builder_predicate (info->metadata, "nfo:pageCount");
		tracker_sparql_builder_object_unvalidated (info->metadata, text);
		break;

	case MS_OFFICE_XML_TAG_NUM_OF_CHARACTERS:
		tracker_sparql_builder_predicate (info->metadata, "nfo:characterCount");
		tracker_sparql_builder_object_unvalidated (info->metadata, text);
		break;

	case MS_OFFICE_XML_TAG_NUM_OF_WORDS:
		tracker_sparql_builder_predicate (info->metadata, "nfo:wordCount");
		tracker_sparql_builder_object_unvalidated (info->metadata, text);
		break;

	case MS_OFFICE_XML_TAG_NUM_OF_LINES:
		tracker_sparql_builder_predicate (info->metadata, "nfo:lineCount");
		tracker_sparql_builder_object_unvalidated (info->metadata, text);
		break;

	case MS_OFFICE_XML_TAG_NUM_OF_PARAGRAPHS:

		break;

	case MS_OFFICE_XML_TAG_DOCUMENT_CORE_DATA:
	case MS_OFFICE_XML_TAG_DOCUMENT_TEXT_DATA:

		break;

	case MS_OFFICE_XML_TAG_INVALID:

		break;
	}
}
