gdk_pixbuf_gdk_pixbuf_animation_new_from_file(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj filename_scm;
  const char * filename;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-pixbuf-animation-new-from-file");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  filename_scm = SCM_SUBRARGS[0];
  if (!SCM_STRINGP(filename_scm)) Scm_Error("<const-char*> required, but got %S", filename_scm);
  filename = CONST_CHAR_PTR(filename_scm);
  {
GError *perr = NULL;
  GdkPixbufAnimation *buf = gdk_pixbuf_animation_new_from_file(filename, &perr);
  if (buf == NULL) {

    Scm_Error("Pixbuf open failed: %s", perr->message);
  }
  SCM_RETURN(SCM_MAKE_GDK_PIXBUF_ANIMATION(buf));
  }
}
