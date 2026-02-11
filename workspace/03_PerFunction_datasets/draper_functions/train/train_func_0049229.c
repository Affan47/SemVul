cdiInqContents(stream_t * streamptr)
{
  int filetype;
  int vlistID;
  int taxisID;
  int status = 0;

  filetype = streamptr->filetype;

  switch (filetype)
    {
#if  defined  (HAVE_LIBGRIB)
    case FILETYPE_GRB:
    case FILETYPE_GRB2:
      {
        status = grbInqContents(streamptr);
	break;
      }
#endif
#if  defined  (HAVE_LIBSERVICE)
    case FILETYPE_SRV:
      {
        status = srvInqContents(streamptr);
	break;
      }
#endif
#if  defined  (HAVE_LIBEXTRA)
    case FILETYPE_EXT:
      {
        status = extInqContents(streamptr);
	break;
      }
#endif
#if  defined  (HAVE_LIBIEG)
    case FILETYPE_IEG:
      {
        status = iegInqContents(streamptr);
	break;
      }
#endif
#if  defined  (HAVE_LIBNETCDF)
    case FILETYPE_NC:
    case FILETYPE_NC2:
    case FILETYPE_NC4:
    case FILETYPE_NC4C:
      {
        status = cdfInqContents(streamptr);
	break;
      }
#endif
    default:
      {
	if ( CDI_Debug )
	  Message("%s support not compiled in!", strfiletype(filetype));

	status = CDI_ELIBNAVAIL;
        break;
      }
    }

  if ( status == 0 )
    {
      vlistID = streamptr->vlistID;
      taxisID = vlistInqTaxis(vlistID);
      if ( taxisID != -1 )
        {
          taxis_t *taxisptr1 = &streamptr->tsteps[0].taxis;
          taxis_t *taxisptr2 = taxisPtr(taxisID);
          ptaxisCopy(taxisptr2, taxisptr1);
          if ( taxisptr1->name     ) taxisptr2->name = taxisptr1->name;
          if ( taxisptr1->longname ) taxisptr2->longname = taxisptr1->longname;
        }
    }

  return (status);
}
