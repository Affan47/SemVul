ANIannlen(int32 ann_id )
{
    CONSTR(FUNC, "ANIannlen");
    ANnode    *ann_node   = NULL;
    int32      file_id = FAIL;
    int32      type;
    int32      ann_key;
    uint16     ann_tag;
    uint16     ann_ref;
    int32      ann_length =(-1);
    int32      ret_value  = SUCCEED;


    HEclear();


    ann_node = HAatom_object(ann_id);
    if (NULL == ann_node)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    file_id = ann_node->file_id;
    ann_key = ann_node->ann_key;
    type    = AN_KEY2TYPE(ann_key);
    ann_ref = AN_KEY2REF(ann_key);


    if (file_id == FAIL)
        HE_REPORT_GOTO("bad file_id", FAIL);


    switch((int32)type)
      {
      case AN_DATA_LABEL:
          ann_tag = DFTAG_DIL;
          break;
      case AN_DATA_DESC:
          ann_tag = DFTAG_DIA;
          break;
      case AN_FILE_LABEL:
          ann_tag = DFTAG_FID;
          break;
      case AN_FILE_DESC:
          ann_tag = DFTAG_FD;
          break;
      default:
          HE_REPORT_GOTO("Bad annotation type for this call",FAIL);
      }

    if (ann_tag == DFTAG_DIL || ann_tag == DFTAG_DIA)
      {
          if ((ann_length = Hlength(file_id, ann_tag, ann_ref)) == FAIL)
              HE_REPORT_GOTO("Failed to find annotation length", FAIL);
          ann_length -= 4;
      }
    else if (ann_tag == DFTAG_FID || ann_tag == DFTAG_FD)
      {
          if ((ann_length = Hlength(file_id, ann_tag, ann_ref)) == FAIL)
              HE_REPORT_GOTO("Failed to find annotation length", FAIL);
      }


    ret_value = (ann_length);

  done:
    if(ret_value == FAIL)
      {

      }


    return ret_value;
}
