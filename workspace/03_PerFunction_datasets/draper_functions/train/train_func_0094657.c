caption() const
{
  FormWidgetButton* fwb = static_cast<FormWidgetButton*>(m_formData->fm);
  QString ret;
  if (fwb->getButtonType() == formButtonPush)
  {
    Dict *dict = m_formData->fm->getObj()->getDict();
    Object obj1;
    if (dict->lookup("MK", &obj1)->isDict())
    {
      AnnotAppearanceCharacs appearCharacs(obj1.getDict());
      if (appearCharacs.getNormalCaption())
      {
        ret = UnicodeParsedString(appearCharacs.getNormalCaption());
      }
    }
    obj1.free();
  }
  else
  {
    if (const char *goo = fwb->getOnStr())
    {
      ret = QString::fromUtf8(goo);
    }
  }
  return ret;
}
