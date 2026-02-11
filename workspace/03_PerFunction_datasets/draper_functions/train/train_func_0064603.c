setDefaultFileType(char *filetypestr, int labort)
{
  if ( filetypestr )
    {
      char *ftstr = filetypestr;

      if      ( memcmp(filetypestr, "grb2", 4)  == 0 ) { ftstr += 4; cdoDefaultFileType = FILETYPE_GRB2;}
      else if ( memcmp(filetypestr, "grb1", 4)  == 0 ) { ftstr += 4; cdoDefaultFileType = FILETYPE_GRB; }
      else if ( memcmp(filetypestr, "grb",  3)  == 0 ) { ftstr += 3; cdoDefaultFileType = FILETYPE_GRB; }
      else if ( memcmp(filetypestr, "nc2",  3)  == 0 ) { ftstr += 3; cdoDefaultFileType = FILETYPE_NC2; }
      else if ( memcmp(filetypestr, "nc4c", 4)  == 0 ) { ftstr += 4; cdoDefaultFileType = FILETYPE_NC4C;}
      else if ( memcmp(filetypestr, "nc4",  3)  == 0 ) { ftstr += 3; cdoDefaultFileType = FILETYPE_NC4; }
      else if ( memcmp(filetypestr, "nc",   2)  == 0 ) { ftstr += 2; cdoDefaultFileType = FILETYPE_NC;  }
      else if ( memcmp(filetypestr, "srv",  3)  == 0 ) { ftstr += 3; cdoDefaultFileType = FILETYPE_SRV; }
      else if ( memcmp(filetypestr, "ext",  3)  == 0 ) { ftstr += 3; cdoDefaultFileType = FILETYPE_EXT; }
      else if ( memcmp(filetypestr, "ieg",  3)  == 0 ) { ftstr += 3; cdoDefaultFileType = FILETYPE_IEG; }
      else
	{
	  if ( labort )
	    {
	      fprintf(stderr, "Unsupported filetype %s!\n", filetypestr);
	      fprintf(stderr, "Available filetypes: grb/grb2/nc/nc2/nc4/nc4c/srv/ext/ieg\n");
	      exit(EXIT_FAILURE);
	    }
	  else
	    {
	      return;
	    }
	}

      if ( cdoDefaultFileType != CDI_UNDEFID && *ftstr != 0 )
	{
	  if ( *ftstr == '_' )
	    {
	      ftstr++;

	      setDefaultDataType(ftstr);
	    }
	  else
	    {
	      fprintf(stderr, "Unexpected character >%c< in file type >%s<!\n", *ftstr, filetypestr);
	      fprintf(stderr, "Use format[_nbits] with:\n");
	      fprintf(stderr, "    format = grb, grb2, nc, nc2, nc4, nc4c, srv, ext or ieg\n");
	      fprintf(stderr, "    nbits  = 32/64 for grb2/nc/nc2/nc4/nc4c/srv/ext/ieg; 1 - 24 for grb/grb2\n");
	      exit(EXIT_FAILURE);
	    }
	}
    }
}
