on_load_example_session_activate       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)

{
  int lp;
  for(lp=1;lp<=MAX_WINS; lp++) {
    if(   sp->im_widget[lp] &&
#ifdef IS_PLYMORPH
	  sp->im_ply_labels_unsaved[lp]
#else
	  sp->im_mesh[lp].changed>0
#endif
	  ) {
      show_error(_("Loading the example session may ruin your current session. Please properly save all meshes and retry."));
      return;
    }
  }
  gchar *P=NULL;
#ifdef  __WIN32__
  extern gchar *program_install_dir;
  gchar *pp[]={".",program_install_dir,NULL};
  gchar *ee[]={"example/ad/gtkmorph.session",
	       "example/AD/gtkmorph.session",NULL};
  lp=0; int le=0;
  while(P == NULL && ee[le]) {
    while(P == NULL && pp[lp]) {
      if(P==NULL) {
	P= g_build_filename(pp[lp],ee[le],NULL);
	if(!g_file_test(P,  G_FILE_TEST_IS_REGULAR)) {
	  g_free(P);P=NULL;
	}
      }
      lp++;
    }
    le++;
  }
#else
  if(P==NULL &&
     g_file_test(DATADIR "/" PACKAGE "/example/AD/gtkmorph.session",  G_FILE_TEST_IS_REGULAR))
    P=g_strdup(DATADIR "/" PACKAGE "/example/AD/gtkmorph.session");
  if(P==NULL) {
    gchar *s;
    if(g_file_test("/etc/debian_version", G_FILE_TEST_IS_REGULAR))

      s=g_strdup_printf(_("The 'example' directory should be in '%s' but is not.\nInstall the 'gtkmorph-example' debian package."),
			DATADIR "/" PACKAGE );
    else
      s=g_strdup_printf(_("The 'example' directory should be in '%s' but is not."),
			DATADIR "/" PACKAGE);
    show_error(s); g_free(s);
  }
#endif
  if(P) {
    g_debug("loading example session from '%s'",P);
    load_session(0,P);
    g_free(P);
  } else g_warning("could not locate example session!");
}
