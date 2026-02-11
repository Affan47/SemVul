output_basisinfo(const BasisInfoStruct & basisInfo)
{
  static char shell_names[] = "SPDFGHIJKLMNOP";
  do_output(LOG_CAT_INFO, LOG_AREA_INTEGRALS, "=============== start of output_basisinfo ===========================");
  do_output(LOG_CAT_INFO, LOG_AREA_INTEGRALS, "output_basisinfo, basisInfo->noOfShells = %i",
	    basisInfo.noOfShells);
  char line[180];
  for(int i = 0; i < basisInfo.noOfShells; i++) {
    if(basisInfo.shellList[i].shellType >=0 &&
       basisInfo.shellList[i].shellType<(signed)sizeof(shell_names))
      do_output(LOG_CAT_INFO, LOG_AREA_INTEGRALS, "%c-shell at (x y z) = ( %8.4f %8.4f %8.4f )"
		" %d primitive(s)",
		shell_names[basisInfo.shellList[i].shellType],
		(double)basisInfo.shellList[i].centerCoords[0],
		(double)basisInfo.shellList[i].centerCoords[1],
		(double)basisInfo.shellList[i].centerCoords[2],
		basisInfo.shellList[i].noOfContr);
    else
      do_output(LOG_CAT_INFO, LOG_AREA_INTEGRALS, "shell with L=%d at (x y z) = ( %8.4f %8.4f %8.4f )"
		" %d primitive(s)",
		basisInfo.shellList[i].shellType,
		(double)basisInfo.shellList[i].centerCoords[0],
		(double)basisInfo.shellList[i].centerCoords[1],
		(double)basisInfo.shellList[i].centerCoords[2],
		basisInfo.shellList[i].noOfContr);
    int pos = 0;
    for(int j = 0; j < basisInfo.shellList[i].noOfContr; j++) {
      sprintf(line+pos, "%10.6f e^%9.6f,",
	      (double)basisInfo.shellList[i].coeffList[j],
	      (double)basisInfo.shellList[i].exponentList[j]);
      pos = (int)strlen(line);
      if(pos>60) { do_output(LOG_CAT_INFO, LOG_AREA_INTEGRALS, line); pos = 0; }
    }
    if(pos>0) do_output(LOG_CAT_INFO, LOG_AREA_INTEGRALS, line);
  }
  do_output(LOG_CAT_INFO, LOG_AREA_INTEGRALS, "================ end of output_basisinfo ===========================");
  return 0;
}
