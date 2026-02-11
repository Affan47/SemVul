utl_SetIndexDelimiter (opn_del)

char opn_del;

  {
  unsigned int i;

  for (i=0 ; i<UTL_DLM__OTHERS ; i++)
    {
    if (UTL_DLM_LEFT [i] == opn_del)
      break;
    }

  UTL_DLM_LEFT      [i] = opn_del;
  UTL_IDX_DELIMITER     = i      ;

  return (i);
  }
