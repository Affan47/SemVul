gerbv_file_version(scheme *sc, pointer args)
{
    pointer car_el;
    int r;
    char *vstr;
    char *tmps;

    dprintf("--> entering project.c:%s()\n", __FUNCTION__);

    if (!sc->vptr->is_pair(args)){
	GERB_MESSAGE("gerbv-file-version!: Too few arguments\n");
	return sc->F;
    }

    car_el = sc->vptr->pair_car(args);
    vstr = get_value_string(sc, car_el);


    r = version_str_to_int( vstr );

    if( r == -1) {
      r = version_str_to_int( GERBV_DEFAULT_PROJECT_FILE_VERSION );
      GERB_MESSAGE("The project file you are attempting to load has specified that it\n"
		   "uses project file version \"%s\" but this string is not\n"
		   "a valid version.  Gerbv will attempt to load the file using\n"
		   "version \"%s\".  You may experience unexpected results.\n",
		   vstr, version_int_to_str( r ));
      vstr = GERBV_DEFAULT_PROJECT_FILE_VERSION;
    }
    if( DEBUG ) {
      tmps = version_int_to_str( r );
      printf ("%s():  Read a project file version of %s (%d)\n", __FUNCTION__, vstr, r);
      printf ("      Translated back to \"%s\"\n", tmps);
      g_free (tmps);
    }

    dprintf ("%s():  Read a project file version of %s (%d)\n", __FUNCTION__, vstr, r);

    if ( r > version_str_to_int( GERBV_PROJECT_FILE_VERSION )) {

	GERB_MESSAGE("The project file you are attempting to load is version \"%s\"\n"
	    "but this copy of gerbv is only capable of loading project files\n"
	    "using version \"%s\" or older.  You may experience unexpected results.",
		     vstr, GERBV_PROJECT_FILE_VERSION);
    } else {
      int i = 0;
      int vok = 0;

      while( known_versions[i] != NULL ) {
	if( strcmp( known_versions[i], vstr) == 0 ) {
	  vok = 1;
	}
	i++;
      }

      if( ! vok ) {


	GERB_MESSAGE("The project file you are attempting to load is version \"%s\"\n"
		     "which is an unknown version.\n"
		     "You may experience unexpected results.",
		     vstr);

      }
    }


    current_file_version = r;

    return sc->NIL;
}
