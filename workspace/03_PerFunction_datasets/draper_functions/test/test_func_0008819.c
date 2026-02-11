demangle_nested_args (struct work_stuff *work, const char **mangled,
                      string *declp)
{
  string* saved_previous_argument;
  int result;
  int saved_nrepeats;


  ++work->forgetting_types;


  saved_previous_argument = work->previous_argument;
  saved_nrepeats = work->nrepeats;
  work->previous_argument = 0;
  work->nrepeats = 0;


  result = demangle_args (work, mangled, declp);


  if (work->previous_argument)
    {
      string_delete (work->previous_argument);
      free ((char *) work->previous_argument);
    }
  work->previous_argument = saved_previous_argument;
  --work->forgetting_types;
  work->nrepeats = saved_nrepeats;

  return result;
}
