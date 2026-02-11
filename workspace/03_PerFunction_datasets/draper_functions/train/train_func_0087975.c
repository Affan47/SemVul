getTemplateTypeParmString(
       const TemplateTypeParmType *ParmTy,
       const TemplateArgument *Args,
       unsigned NumArgs,
       std::string &Str)
{
  unsigned Idx = ParmTy->getIndex();

  if (Idx >= NumArgs)
    return false;
  const TemplateArgument Arg = Args[Idx];
  if (Arg.getKind() != TemplateArgument::Type)
    return false;
  QualType ArgQT = Arg.getAsType();
  ArgQT.getAsStringInternal(Str, Context->getPrintingPolicy());
  return true;
}
