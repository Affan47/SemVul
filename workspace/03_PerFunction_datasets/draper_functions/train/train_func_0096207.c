gtksettings_gtk_settings_set_long_property(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj settings_scm;
  GtkSettings* settings;
  ScmObj name_scm;
  const gchar * name;
  ScmObj v_long_scm;
  long v_long;
  ScmObj origin_scm;
  const gchar * origin;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-settings-set-long-property");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  settings_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_SETTINGS_P(settings_scm)) Scm_Error("<gtk-settings> required, but got %S", settings_scm);
  settings = SCM_GTK_SETTINGS(settings_scm);
  name_scm = SCM_SUBRARGS[1];
  if (!SCM_STRINGP(name_scm)) Scm_Error("<const-gchar*> required, but got %S", name_scm);
  name = CONST_GCHAR_PTR(name_scm);
  v_long_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(v_long_scm)) Scm_Error("C long integer required, but got %S", v_long_scm);
  v_long = Scm_GetInteger(v_long_scm);
  origin_scm = SCM_SUBRARGS[3];
  if (!SCM_STRINGP(origin_scm)) Scm_Error("<const-gchar*> required, but got %S", origin_scm);
  origin = CONST_GCHAR_PTR(origin_scm);
  {
gtk_settings_set_long_property(settings, name, v_long, origin);
SCM_RETURN(SCM_UNDEFINED);
  }
}
