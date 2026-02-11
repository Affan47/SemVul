get_vdate(int vlistID)
{
  int vdate = 0;
  int natts;
  int i, len, type;
  char name[CDI_MAX_NAME];
  char attstr[CDI_MAX_NAME];

  vlistInqNatts(vlistID, CDI_GLOBAL, &natts);

  for ( i = 0; i < natts; ++i )
    {
      vlistInqAtt(vlistID, CDI_GLOBAL, i, name, &type, &len);
      if ( type == DATATYPE_TXT )
	{
	  if ( strcmp(name, "DateAndTime") == 0 ||
	       strcmp(name, "Date_Time") == 0 )
	    {
	      vlistInqAttTxt(vlistID, CDI_GLOBAL, name, CDI_MAX_NAME, attstr);
	      if ( len > 8 ) len = 8;
	      attstr[len] = 0;
	      vdate = atoi(attstr);
	      if ( vdate < 999999 ) vdate = vdate*100 + 1;
	    }
	}
    }

  return (vdate);
}
