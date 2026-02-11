considerNamer(const AttributeList &atts,
			    Boolean &inhibitCache,
			    unsigned &arcNamerIndex)
{
  arcNamerIndex = invalidAtt;
  if (supportAtts_[rArcNamrA].size() == 0
      || !atts.attributeIndex(supportAtts_[rArcNamrA], arcNamerIndex))
    return 0;
  if (atts.current(arcNamerIndex) || atts.specified(arcNamerIndex))
    inhibitCache = 1;
  const AttributeValue *val = atts.value(arcNamerIndex);
  if (!val)
    return 0;
  return val->text();
}
