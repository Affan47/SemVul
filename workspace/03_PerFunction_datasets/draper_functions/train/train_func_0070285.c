pilDfsCreateDB(int grp_ifs, PilCdbKeyCase key_case)
{


  if (cfgDB)
    return EXIT_FAILURE;
  else {


    if ((cfgDB = newPilCdb()) == NULL)
      return EXIT_FAILURE;

    pilCdbSetKeyCase(cfgDB, key_case);


    if (grp_ifs != 0) {


      if ((isspace)(grp_ifs) || !(ispunct)(grp_ifs)) {
	deletePilCdb(cfgDB);
	return EXIT_FAILURE;
      }

      if (pilCdbSetGroupIFS(cfgDB, (char)grp_ifs) == EXIT_FAILURE) {
	deletePilCdb(cfgDB);
	return EXIT_FAILURE;
      }
    }


    if (pilDfsInitDB() == EXIT_FAILURE) {
      deletePilCdb(cfgDB);
      return EXIT_FAILURE;
    }
  }


  return EXIT_SUCCESS;

}
