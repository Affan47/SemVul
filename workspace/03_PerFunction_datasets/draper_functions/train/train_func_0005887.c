genders_filename_get(genders_filename_type_t type)
{
  char *filename = NULL;

  switch (type)
    {
    case GENDERS_FILENAME_NULL:
      filename = NULL;
      break;
    case GENDERS_FILENAME_NON_NULL_EMPTY:
      filename = "";
      break;
    case GENDERS_FILENAME_NON_NULL_EXIST:
      filename = genders_database_corner_case.filename;
      break;
    case GENDERS_FILENAME_NON_NULL_NOT_EXIST:
      filename = genders_database_not_exist.filename;
      break;
    default:
      genders_err_exit("genders_handle_get: invalid type: %d\n", type);
    }

  return filename;
}
