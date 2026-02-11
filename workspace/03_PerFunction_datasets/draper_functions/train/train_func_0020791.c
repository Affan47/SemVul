DFR8Iopen(const char *filename, intn acc_mode)
{
  CONSTR(FUNC, "DFR8Iopen");
  int32       file_id;
  int32       ret_value = SUCCEED;


  if (HDstrncmp(Lastfile, filename, DF_MAXFNLEN) || (acc_mode == DFACC_CREATE))
    {

      if ((file_id = Hopen(filename, acc_mode, 0)) == FAIL)
        HGOTO_ERROR(DFE_BADOPEN, FAIL);
      foundRig = -1;
      Refset = 0;
      Newdata = 0;
      Readrig = Zrig;
      Writerig = Zrig;
      if (Newpalette != (-1))
        Newpalette = 1;
    }
  else
    {
      if ((file_id = Hopen(filename, acc_mode, 0)) == FAIL)
        HGOTO_ERROR(DFE_BADOPEN, FAIL);
    }


  HDstrncpy(Lastfile, filename, DF_MAXFNLEN);

  ret_value = file_id;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
