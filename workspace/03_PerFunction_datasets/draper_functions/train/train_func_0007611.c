parse_uint64(const char* option_name, const char* arg, uint64_t* retval)
{
  char* endptr;
  *retval = strtoull(arg, &endptr, 0);
  if (*endptr != '\0')
    gold_fatal(_("%s: invalid option value (expected an integer): %s"),
	       option_name, arg);
}
