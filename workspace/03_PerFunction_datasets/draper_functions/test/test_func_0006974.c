addPresentationContext(T_ASC_Parameters *params,
  int presentationContextId,
  const OFString &abstractSyntax,
  const OFString &transferSyntax,
  T_ASC_SC_ROLE proposedRole = ASC_SC_ROLE_DEFAULT)
{
  const char *c_p = transferSyntax.c_str();
  OFCondition cond = ASC_addPresentationContext(params, presentationContextId,
    abstractSyntax.c_str(), &c_p, 1, proposedRole);
  return cond;
}
