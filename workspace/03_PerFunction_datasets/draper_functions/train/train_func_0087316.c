Scm_PangoAttrFontDescClass_start_index_GET(ScmObj OBJARG)
{
  PangoAttrFontDesc* obj = SCM_PANGO_ATTR_FONT_DESC(OBJARG);
return Scm_MakeIntegerU(obj->attr.start_index);
}
