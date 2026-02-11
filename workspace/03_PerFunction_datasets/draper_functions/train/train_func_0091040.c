beh_namelist (pt_exp)

struct chain *pt_exp;

  {
  struct chain *res_chain    = NULL;
  struct chain *tmp_chain    = NULL;
  struct chain *pt_opr       ;
  char         *name         ;

  static char  *str_z        = NULL;
  static char  *str_o        = NULL;
  static char  *str_d        = NULL;
  static char   buffer [128] ;


  if (str_z == NULL)
    {
    str_z = namealloc ("'0'");
    str_o = namealloc ("'1'");
    str_d = namealloc ("'d'");
    }

  if (pt_exp != NULL)
    {


    if (pt_exp->NEXT != NULL)
      {


      if (((long) ((struct chain *) pt_exp->DATA)->DATA) == STABLE)
        {
        name      = ((struct chain *) pt_exp->NEXT->DATA)->DATA;
        res_chain = addchain (NULL, name);
        sprintf   (buffer, "%s'delayed", name);
        name      = namealloc (buffer);
        res_chain = addchain (res_chain, name);
        }
      else
        {
        pt_opr = pt_exp->NEXT;
        while (pt_opr != NULL)
          {
          tmp_chain = beh_namelist (pt_opr->DATA);
          res_chain = append (res_chain, tmp_chain);
          pt_opr    = pt_opr->NEXT;
          }
        }
      }
    else
      {


      if ((pt_exp->DATA != str_z) && (pt_exp->DATA != str_o) &&
          (pt_exp->DATA != str_d)    )
        {
        res_chain = addchain (NULL, pt_exp->DATA);
        }
      }
    }

  return (res_chain);
  }
