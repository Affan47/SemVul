matches (MatchTemplateArg &arg) const {
  return arg.is_type () && _match_type.matches (((MTA_Type&)arg)._match_type);
}
