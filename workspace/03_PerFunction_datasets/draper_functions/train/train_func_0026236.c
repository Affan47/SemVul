mailmime_discrete_type_write_driver(int (* do_write)(void *, const char *, size_t), void * data, int * col,
			     struct mailmime_discrete_type * discrete_type)
{
  int r;

  switch (discrete_type->dt_type) {
  case MAILMIME_DISCRETE_TYPE_TEXT:
    r = mailimf_string_write_driver(do_write, data, col, "text", 4);
    break;

  case MAILMIME_DISCRETE_TYPE_IMAGE:
    r = mailimf_string_write_driver(do_write, data, col, "image", 5);
    break;

  case MAILMIME_DISCRETE_TYPE_AUDIO:
    r = mailimf_string_write_driver(do_write, data, col, "audio", 5);
    break;

  case MAILMIME_DISCRETE_TYPE_VIDEO:
    r = mailimf_string_write_driver(do_write, data, col, "video", 5);
    break;

  case MAILMIME_DISCRETE_TYPE_APPLICATION:
    r = mailimf_string_write_driver(do_write, data, col, "application", 11);
    break;

  case MAILMIME_DISCRETE_TYPE_EXTENSION:
    r = mailimf_string_write_driver(do_write, data, col, discrete_type->dt_extension,
			     strlen(discrete_type->dt_extension));
    break;

  default:
    r = MAILIMF_ERROR_INVAL;
    break;
  }

  if (r != MAILIMF_NO_ERROR)
    return r;

  return MAILIMF_NO_ERROR;
}
