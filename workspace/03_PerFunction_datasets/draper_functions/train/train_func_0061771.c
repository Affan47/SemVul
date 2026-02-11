FindSessionRedirect(const buzz::XmlElement* stanza,
                         SessionRedirect* redirect) {
  const buzz::XmlElement* error_elem = GetXmlChild(stanza, LN_ERROR);
  if (error_elem == NULL)
    return false;

  const buzz::XmlElement* redirect_elem =
      error_elem->FirstNamed(QN_GINGLE_REDIRECT);
  if (redirect_elem == NULL)
    redirect_elem = error_elem->FirstNamed(buzz::QN_STANZA_REDIRECT);
  if (redirect_elem == NULL)
    return false;

  if (!GetUriTarget(STR_REDIRECT_PREFIX, redirect_elem->BodyText(),
                    &redirect->target))
    return false;

  return true;
}
