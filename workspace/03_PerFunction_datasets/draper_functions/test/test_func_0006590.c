government_by_rule_name(const char *name)
{
  const char *qname = Qn_(name);

  governments_iterate(gov) {
    if (0 == fc_strcasecmp(government_rule_name(gov), qname)) {
      return gov;
    }
  } governments_iterate_end;

  return NULL;
}
