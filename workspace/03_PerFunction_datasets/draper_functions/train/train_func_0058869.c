volume_read_xml(AmitkObject * object, xmlNodePtr nodes, FILE * study_file, gchar * error_buf) {

  AmitkVolume * volume;

  error_buf = AMITK_OBJECT_CLASS(parent_class)->object_read_xml(object, nodes, study_file, error_buf);

  volume = AMITK_VOLUME(object);

  volume->corner = amitk_point_read_xml(nodes, "corner", &error_buf);
  volume->valid = xml_get_boolean(nodes, "valid", &error_buf);


  if (!volume->valid)
    if (!POINT_EQUAL(volume->corner, zero_point))
      volume->valid = TRUE;

  return error_buf;
}
