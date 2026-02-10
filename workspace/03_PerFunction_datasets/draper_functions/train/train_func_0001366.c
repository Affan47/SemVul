updateStringAttributeValue(DcmItem *dataset, const DcmTagKey &key, OFString &value)
{
  DcmStack stack;
  DcmTag tag(key);

  OFCondition cond = EC_Normal;
  cond = dataset->search(key, stack, ESM_fromHere, OFFalse);
  if (cond != EC_Normal) {
    OFLOG_ERROR(storescuLogger, "updateStringAttributeValue: cannot find: " << tag.getTagName()
         << " " << key << ": " << cond.text());
    return OFFalse;
  }

  DcmElement *elem = OFstatic_cast(DcmElement *, stack.top());

  DcmVR vr(elem->ident());
  if (elem->getLength() > vr.getMaxValueLength()) {
    OFLOG_ERROR(storescuLogger, "updateStringAttributeValue: INTERNAL ERROR: " << tag.getTagName()
         << " " << key << ": value too large (max " << vr.getMaxValueLength()
         << ") for " << vr.getVRName() << " value: " << value);
    return OFFalse;
  }

  cond = elem->putOFStringArray(value);
  if (cond != EC_Normal) {
    OFLOG_ERROR(storescuLogger, "updateStringAttributeValue: cannot put string in attribute: " << tag.getTagName()
         << " " << key << ": " << cond.text());
    return OFFalse;
  }

  return OFTrue;
}
