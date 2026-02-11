decodeReferralParams (
	char	*val)
{
  if (val == NULL)
  {
    fprintf (stderr, "Error: missing arg referral\n");
    return (-1);
  }
  if (!strcmp (val, "on"))
    return (REFERRAL_ON);
  if (!strcmp (val, "off"))
    return (REFERRAL_OFF);
  if (!strcmp (val, "rebind"))
    return (REFERRAL_REBIND);

  fprintf (stderr, "Error: illegal arg %s for referral\n", val);
  return (-1);
}
