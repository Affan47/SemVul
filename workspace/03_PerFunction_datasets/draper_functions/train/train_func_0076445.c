getFieldByGuiName(const char* name, const char* index, bool is_pre_indexed, bool only_active)
{
  if ( index == NULL ) {
    return getFieldByGuiName(name, only_active);
  }

  for (short i = 0; i < nofFields; i++) {

    ParameterField* pf = fields[i];

    if ( LibFront::in(name, pf->getGuiName()) &&
         LibFront::in(index, pf->getGuiIndex()) &&
         ( (is_pre_indexed && pf->isPreIndexed()) ||
           (!is_pre_indexed && pf->isPostIndexed())
         )
         ) {


      if ( only_active && !pf->isActiveInstance() ) {
        return NULL;
      } else {
        return pf;
      }
    }
  }

  return NULL;
}
