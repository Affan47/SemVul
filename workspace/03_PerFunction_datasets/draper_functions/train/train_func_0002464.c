report_print_custom_section(const seaudit_log_t * log, const seaudit_report_t * report,
				       xmlTextReaderPtr reader, xmlChar * title, FILE * outfile)
{
	size_t len, i;
	int rt, error = 0, retval = -1, end_of_element = 0;
	xmlChar *view_filePath = NULL, *name = NULL;

	if (title != NULL) {
		if (report->format == SEAUDIT_REPORT_FORMAT_HTML) {
			fprintf(outfile, "<h2 class=\"custom_section_title\"><u>%s</h2></u>\n", title);
		} else {
			fprintf(outfile, "%s\n", title);
			len = strlen((char *)title);
			for (i = 0; i < len; i++) {
				fprintf(outfile, "-");
			}
			fprintf(outfile, "\n");
		}
	}


	rt = xmlTextReaderRead(reader);
	while (rt == 1) {

		name = xmlTextReaderName(reader);
		if (name == NULL) {
			error = errno;
			ERR(log, "%s", "Unavailable node name within.");
			goto cleanup;
		}


		if (strcmp((char *)name, "custom-section") == 0 && xmlTextReaderNodeType(reader) == 15) {
			xmlFree(name);
			end_of_element = 1;
			break;
		}
		if (strcmp((char *)name, "view") == 0 && xmlTextReaderNodeType(reader) == 1 && xmlTextReaderHasAttributes(reader)) {
			view_filePath = xmlTextReaderGetAttribute(reader, (const xmlChar *)"file");
			if (view_filePath == NULL) {
				error = errno;
				ERR(log, "%s", "Error getting file attribute for view node.");
				goto cleanup;
			}
			if (report_print_loaded_view(log, report, view_filePath, outfile) < 0) {
				error = errno;
				goto cleanup;
			}
			xmlFree(view_filePath);
		}
		xmlFree(name);
		rt = xmlTextReaderRead(reader);
	}
	if (!end_of_element && rt != 0) {
		error = EIO;
		ERR(log, "Error parsing config file %s. (rt:%d)", report->config, rt);
		goto cleanup;
	}

	if (!end_of_element) {
		error = EIO;
		ERR(log, "%s", "Encountered end of file before finding end of element for custom-section node.");
		goto cleanup;;
	}
	if (report->format == SEAUDIT_REPORT_FORMAT_HTML)
		fprintf(outfile, "<br>\n");
	else
		fprintf(outfile, "\n");

	return 0;
      cleanup:
	if (view_filePath)
		xmlFree(view_filePath);
	if (name)
		xmlFree(name);
	if (error != 0) {
		errno = error;
	}
	return retval;
}
