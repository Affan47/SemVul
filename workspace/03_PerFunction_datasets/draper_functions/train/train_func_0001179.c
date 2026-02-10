xml_open_doc(gchar * xml_filename, FILE * study_file,
		       guint64 location, guint64 size,
		       gchar ** perror_buf) {


  xmlDocPtr doc;
  gchar * xml_buffer;
  long location_long;
  size_t size_size;
  size_t bytes_read;

  if (study_file == NULL) {
    if ((doc = xmlParseFile(xml_filename)) == NULL) {
      amitk_append_str_with_newline(perror_buf,_("Couldn't Parse AMIDE xml file %s"),xml_filename);
      return NULL;
    }


  } else {


    if (!xml_check_file_32bit_okay(location)) {
      g_warning(_("File to large to read on 32bit platform."));
      return NULL;
    }
    location_long = location;

    if (!xml_check_file_32bit_okay(size)) {
      g_warning(_("File to large to read on 32bit platform."));
      return NULL;
    }
    size_size = size;

    xml_buffer = g_try_new(gchar, size_size);
    g_return_val_if_fail(xml_buffer != NULL, NULL);

    if (fseek(study_file, location_long,SEEK_SET) != 0) {
      amitk_append_str_with_newline(perror_buf, _("Could not seek to location %lx in file."), location_long);
      return NULL;
    }

    bytes_read = fread(xml_buffer, sizeof(gchar), size_size, study_file);
    if (bytes_read != size_size) {
      amitk_append_str_with_newline(perror_buf, _("Only read %x bytes from file, expected %x"), bytes_read, size_size);
      return NULL;
    }


    doc = xmlParseMemory(xml_buffer, size_size);
    g_free(xml_buffer);
  }


  return doc;
}
