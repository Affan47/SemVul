cp_classify_record (tree type)
{
  if (CLASSTYPE_DECLARED_CLASS (type))
    return RECORD_IS_CLASS;

  return RECORD_IS_STRUCT;
}
