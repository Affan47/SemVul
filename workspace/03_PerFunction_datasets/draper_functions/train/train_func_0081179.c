DFSDpre32sdg(char *filename, uint16 ref, intn *ispre32)
{
    uint32      num;
    int32       file_id;
    intn        found = 0;
    DFnsdgle   *ptr;
    intn       ret_value = SUCCEED;
    CONSTR(FUNC, "DFSDpre32sdg");

    HEclear();


    if (library_terminate == FALSE)
        if(DFSDIstart()==FAIL)
            HGOTO_ERROR(DFE_CANTINIT, FAIL);

    file_id = DFSDIopen(filename, DFACC_READ);
    if (file_id == FAIL)
        HGOTO_ERROR(DFE_BADOPEN, FAIL);
    ptr = nsdghdr->nsdg_t;
    num = nsdghdr->size;

    while ((num > 0) && (ptr != NULL) && !found)
      {
          if ((ptr->nsdg.tag == DFTAG_SDG)
              && (ptr->nsdg.ref == ref))
            {
                found = 1;
                *ispre32 = TRUE;
            }
          else if ((ptr->sdg.tag == DFTAG_SDG)
                   && (ptr->sdg.ref == ref))
            {
                found = 1;
                *ispre32 = FALSE;
            }
          else
            {
                ptr = ptr->next;
                num--;
            }
      }

    if (((num == 0) && (ptr != NULL)) || ((num != 0) && (ptr == NULL)) || !found)
      HCLOSE_GOTO_ERROR(file_id, DFE_BADTABLE, FAIL);

    if (Hclose(file_id) < 0)
        ret_value = FAIL;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
