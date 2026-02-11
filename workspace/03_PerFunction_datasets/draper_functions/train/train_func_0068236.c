parse_class (const sc_char *class_)
{
  sc_char class_name[PARSE_TEMP_LENGTH];
  sc_int index_;
  sc_vartype_t vt_key;


  if (sscanf (class_, "<%[^>]", class_name) != 1)
    sc_fatal ("parse_class: error in class, %s\n", class_);
  if (parse_trace)
    sc_trace ("Parse: entering class %s\n", class_name);


  for (index_ = 0; parse_schema[index_].class_name; index_++)
    {
      if (strcmp (parse_schema[index_].class_name, class_name) == 0)
        break;
    }
  if (!parse_schema[index_].class_name)
    sc_fatal ("parse_class: class not described, %s\n", class_name);


  if (index_ > 0)
    {
      vt_key.string = class_ + strlen (class_name) + 2;
      parse_push_key (vt_key, PROP_KEY_STRING);
    }


  parse_descriptor (parse_schema[index_].descriptor);


  if (index_ > 0)
    parse_pop_key ();

  if (parse_trace)
    sc_trace ("Parse: leaving class %s\n", class_name);
}
