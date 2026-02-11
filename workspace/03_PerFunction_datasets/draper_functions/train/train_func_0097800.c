prepare_glk_args(char *proto, dispatch_splot_t *splot)
{
  static gluniversal_t *garglist = NULL;
  static int garglist_size = 0;

  int ix;
  int numwanted, numvargswanted, maxargs;
  char *cx;

  cx = proto;
  numwanted = 0;
  while (*cx >= '0' && *cx <= '9') {
    numwanted = 10 * numwanted + (*cx - '0');
    cx++;
  }
  splot->numwanted = numwanted;

  maxargs = 0;
  numvargswanted = 0;
  for (ix = 0; ix < numwanted; ix++) {
    int isref, passin, passout, nullok, isarray, isretained, isreturn;
    cx = read_prefix(cx, &isref, &isarray, &passin, &passout, &nullok,
      &isretained, &isreturn);
    if (isref) {
      maxargs += 2;
    }
    else {
      maxargs += 1;
    }
    if (!isreturn) {
      if (isarray) {
        numvargswanted += 2;
      }
      else {
        numvargswanted += 1;
      }
    }

    if (*cx == 'I' || *cx == 'C') {
      cx += 2;
    }
    else if (*cx == 'Q') {
      cx += 2;
    }
    else if (*cx == 'S' || *cx == 'U') {
      cx += 1;
    }
    else if (*cx == '[') {
      int refdepth, nwx;
      cx++;
      nwx = 0;
      while (*cx >= '0' && *cx <= '9') {
        nwx = 10 * nwx + (*cx - '0');
        cx++;
      }
      maxargs += nwx;

      refdepth = 1;
      while (refdepth > 0) {
        if (*cx == '[')
          refdepth++;
        else if (*cx == ']')
          refdepth--;
        cx++;
      }
    }
    else {
      fatal_error("Illegal format string.");
    }
  }

  if (*cx != ':' && *cx != '\0')
    fatal_error("Illegal format string.");

  splot->maxargs = maxargs;

  if (splot->numvargs != numvargswanted)
    fatal_error("Wrong number of arguments to Glk function.");

  if (garglist && garglist_size < maxargs) {
    glulx_free(garglist);
    garglist = NULL;
    garglist_size = 0;
  }
  if (!garglist) {
    garglist_size = maxargs + 16;
    garglist = (gluniversal_t *)glulx_malloc(garglist_size
      * sizeof(gluniversal_t));
  }
  if (!garglist)
    fatal_error("Unable to allocate storage for Glk arguments.");

  splot->garglist = garglist;
}
