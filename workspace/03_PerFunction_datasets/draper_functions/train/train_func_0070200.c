tor_validate_process_specifier(const char *process_spec,
                               const char **msg)
{
  struct parsed_process_specifier_t ppspec;

  tor_assert(msg != NULL);
  *msg = NULL;

  return parse_process_specifier(process_spec, &ppspec, msg);
}
