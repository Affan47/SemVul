uid_trust_string_fixed(PKT_public_key *key,PKT_user_id *uid)
{
  if(!key && !uid)


    return _("10 translator see trustdb.c:uid_trust_string_fixed");
  else if(uid->is_revoked || (key && key->is_revoked))
    return                         _("[ revoked]");
  else if(uid->is_expired)
    return                         _("[ expired]");
  else if(key)
    switch(get_validity(key,uid)&TRUST_MASK)
      {
      case TRUST_UNKNOWN:   return _("[ unknown]");
      case TRUST_EXPIRED:   return _("[ expired]");
      case TRUST_UNDEFINED: return _("[  undef ]");
      case TRUST_MARGINAL:  return _("[marginal]");
      case TRUST_FULLY:     return _("[  full  ]");
      case TRUST_ULTIMATE:  return _("[ultimate]");
      }

  return "err";
}
