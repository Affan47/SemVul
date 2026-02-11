genders_getnodes_corner_case(int verbose)
{
  int i = 0;
  int errcount = 0;
  genders_getnodes_corner_case_t *tests = &genders_getnodes_corner_case_tests[0];
  genders_t gh;
  char **list;
  int list_len;

  gh = genders_handle_get(GENDERS_HANDLE_LOADED);
  if ((list_len = genders_nodelist_create(gh, &list)) < 0)
    genders_err_exit("genders_nodelist_create: %s", genders_errormsg(gh));

  while (!(tests[i].num < 0))
    {
      genders_t handle;
      int return_value, errnum, len;
      char **listptr;
      char *attrptr;
      char *valptr;

      handle = genders_handle_get(tests[i].param1);
      listptr = (tests[i].param2 == GENDERS_POINTER_NULL) ? NULL : list;
      len = (tests[i].param3 == GENDERS_LENGTH_POSITIVE_LARGE) ? list_len : tests[i].param3;

      if (tests[i].param4 == GENDERS_STRING_NULL)
	attrptr = NULL;
      else if (tests[i].param4 == GENDERS_STRING_NON_NULL_EMPTY)
	attrptr = "";
      else
	attrptr = genders_database_corner_case.data->attr_with_val;

      if (tests[i].param5 == GENDERS_STRING_NULL)
	valptr = NULL;
      else if (tests[i].param5 == GENDERS_STRING_NON_NULL_EMPTY)
	valptr = "";
      else
	valptr = genders_database_corner_case.data->val;

      return_value = genders_getnodes(handle, listptr, len, attrptr, valptr);
      errnum = genders_errnum(handle);

      errcount += genders_return_value_errnum_check("genders_getnodes",
						    tests[i].num,
						    tests[i].expected_return_value,
						    tests[i].expected_errnum,
						    return_value,
						    errnum,
						    NULL,
						    verbose);

      genders_handle_cleanup(handle);
      i++;
    }

  if (genders_nodelist_destroy(gh, list) < 0)
    genders_err_exit("genders_nodelist_destroy: %s", genders_errormsg(gh));
  if (genders_handle_destroy(gh) < 0)
    genders_err_exit("genders_handle_destroy: %s", genders_errormsg(gh));

  return errcount;
}
