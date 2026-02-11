printAtts(FILE *fp, int vlistID, int varID)
{
#define MAXATT 8192
  int natts, ia;
  char attname[1024];
  int atttype, attlen;
  char atttxt[MAXATT];
  int attint[MAXATT];
  double attflt[MAXATT];
  int i;

  vlistInqNatts(vlistID, varID, &natts);

  for ( ia = 0; ia < natts; ++ia )
    {
      vlistInqAtt(vlistID, varID, ia, attname, &atttype, &attlen);
      if ( atttype == DATATYPE_INT )
	{
	  if ( attlen > MAXATT ) attlen = MAXATT;
	  vlistInqAttInt(vlistID, varID, attname, attlen, attint);
	  fprintf(fp, "  %s=", attname);
	  for ( i = 0; i < attlen; ++i)
	    {
	      if ( i > 0 ) fprintf(fp, ", ");
	      fprintf(fp, "%d", attint[i]);
	    }
	  fprintf(fp, "\n");
	}
      else if ( atttype == DATATYPE_FLT )
	{
	  if ( attlen > MAXATT ) attlen = MAXATT;
	  vlistInqAttFlt(vlistID, varID, attname, MAXATT, attflt);
	  fprintf(fp, "  %s=", attname);
	  for ( i = 0; i < attlen; ++i)
	    {
	      if ( i > 0 ) fprintf(fp, ", ");
	      fprintf(fp, "%g", attflt[i]);
	    }
	  fprintf(fp, "\n");
	}
      else if ( atttype == DATATYPE_TXT )
	{
	  vlistInqAttTxt(vlistID, varID, attname, sizeof(atttxt), atttxt);
	  atttxt[attlen] = 0;
	  fprintf(fp, "  %s=\"%s\"\n", attname, atttxt);
	}
    }
}
