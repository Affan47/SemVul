ANstart(int32 file_id )
{
    CONSTR(FUNC, "ANstart");
    filerec_t  *file_rec = NULL;
    int32       ret_value = SUCCEED;


    HEclear();


    file_rec = HAatom_object(file_id);
    if (BADFREC(file_rec))
        HGOTO_ERROR(DFE_ARGS, FAIL);


    ANIinit();

    ret_value = file_id;

  done:
    if(ret_value == FAIL)
      {
      }


    return ret_value;
}
