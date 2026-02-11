pango_glyph_pango_glyph_string_set_size(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj string_scm;
  PangoGlyphString* string;
  ScmObj new_len_scm;
  int new_len;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("pango-glyph-string-set-size");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  string_scm = SCM_SUBRARGS[0];
  if (!SCM_PANGO_GLYPH_STRING_P(string_scm)) Scm_Error("<pango-glyph-string> required, but got %S", string_scm);
  string = SCM_PANGO_GLYPH_STRING(string_scm);
  new_len_scm = SCM_SUBRARGS[1];
  if (!SCM_INTEGERP(new_len_scm)) Scm_Error("C integer required, but got %S", new_len_scm);
  new_len = Scm_GetInteger(new_len_scm);
  {
pango_glyph_string_set_size(string, new_len);
SCM_RETURN(SCM_UNDEFINED);
  }
}
