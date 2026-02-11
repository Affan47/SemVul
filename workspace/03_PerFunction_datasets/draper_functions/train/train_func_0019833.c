Scm_GtkWindowClass_wmclass_name_SET(ScmObj OBJARG, ScmObj value)
{
  GtkWindow* obj = SCM_GTK_WINDOW(OBJARG);
if (SCM_STRINGP(value)) {obj->wmclass_name = Scm_GetString(SCM_STRING(value));};
}
