PrintFormalCharges()
  {
    IF_OBFF_LOGLVL_LOW {
      OBFFLog("\nF O R M A L   C H A R G E S\n\n");
      OBFFLog("IDX\tCHARGE\n");

      FOR_ATOMS_OF_MOL (a, _mol) {
        snprintf(_logbuf, BUFF_SIZE, "%d\t%f\n", a->GetIdx(), a->GetPartialCharge());
        OBFFLog(_logbuf);
      }
    }
  }
