setOverride(xmlNode* element, bool override)
{
  if(element != NULL)
  {
    xmlSetProp(element, (xmlChar*)"override", (xmlChar*)(override ? "yes" : "no"));

  }
}
