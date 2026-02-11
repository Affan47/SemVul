parse_stack_backtrace (void)
{
  sc_vartype_t vt_key[PARSE_MAX_DEPTH];
  sc_char format[PARSE_MAX_DEPTH];
  sc_int depth, index_;

  parse_retrieve_stack (format, vt_key, &depth);

  sc_error ("parse_stack_backtrace: version %s schema parsed to depth %ld\n",
            (parse_schema == V400_PARSE_SCHEMA) ? "4.00" :
            (parse_schema == V390_PARSE_SCHEMA) ? "3.90" :
            (parse_schema == V380_PARSE_SCHEMA) ? "3.80" : "[Invalid]",
            depth);

  sc_error ("parse_stack_backtrace: parse stack backtrace follows...\n");
  for (index_ = 0; index_ < depth; index_++)
    {
      sc_char type;

      type = format[index_];
      if (type == PROP_KEY_INTEGER)
        sc_error ("%2ld - [%c] %ld\n", index_, type, vt_key[index_].integer);
      else if (type == PROP_KEY_STRING)
        sc_error ("%2ld - [%c] \"%s\"\n", index_, type, vt_key[index_].string);
      else
        sc_error ("%2ld - [%c] %p\n", index_, type, vt_key[index_].voidp);
    }
}
