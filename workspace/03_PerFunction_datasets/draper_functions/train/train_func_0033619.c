HDisnetcdf(filename)
const char * filename;
{

    static const char *FUNC = "HDisnetcdf";
    hdf_file_t fp;
    uint8      b[4];
    uint8    * bb = NULL;
    int32      magic_num;
    intn       ret_value = TRUE;

    fp = (hdf_file_t)HI_OPEN(filename, DFACC_READ);
    if (OPENERR(fp))
      {
        ret_value = FALSE;
        goto done;
      }
    else
      {
        if(HI_READ(fp, b, 4) == FAIL)
          {
              HERROR(DFE_READERROR);
              HI_CLOSE(fp);
              ret_value = FALSE;
              goto done;
          }

        bb = &b[0];

        INT32DECODE(bb, magic_num);

        if(magic_num == NCMAGIC)
            ret_value = TRUE;
        else
            ret_value = FALSE;

        HI_CLOSE(fp);
    }

done:
    if (ret_value == FALSE)
      {

      }


    return ret_value;
}
