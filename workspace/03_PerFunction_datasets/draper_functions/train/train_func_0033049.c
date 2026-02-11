utl_GetVhdlSlicedName (pt_lst)

struct utchn **pt_lst;

  {
  struct utchn *pt_chn                = NULL;
  int           indx                  ;
  int           left                  ;
  int           right                 ;
  int           incr                  = 0   ;
  char         *name                  = NULL;
  char          buf [UTL_STR__MAXLEN] ;


  if (pt_lst != NULL)
    {
    pt_chn = *pt_lst;
    if (pt_chn != NULL)
      {
      left = utl_GetNameIndex ((char *) pt_chn->DATA.VPNT, ' ');

      if (left == -1)
        {
        name   = (char *) pt_chn->DATA.VPNT;
        pt_chn =          pt_chn->NEXT     ;
        }
      else
        {
        name   = utl_GetRHeaderString ((char *) pt_chn->DATA.VPNT, ' ');
        pt_chn = pt_chn->NEXT;

        while (pt_chn != NULL)
          {
          if (name != utl_GetRHeaderString ((char *) pt_chn->DATA.VPNT, ' '))
            break;

          indx = utl_GetNameIndex ((char *) pt_chn->DATA.VPNT, ' ');
          if (incr == 0)
            {
            right = indx;

            if      (indx == (left + 1)) incr =  1;
            else if (indx == (left - 1)) incr = -1;
            else                         break    ;
            }
          else
            {
            if (indx == (right + incr))
              right = indx;
            else
              break;
            }

          pt_chn = pt_chn->NEXT;
          }

        if (incr ==  0) sprintf (buf, "%s (%d)"          , name, left       );
        if (incr ==  1) sprintf (buf, "%s (%d to %d)"    , name, left, right);
        if (incr == -1) sprintf (buf, "%s (%d downto %d)", name, left, right);

        name = utl_SaveString (buf);
        }

      *pt_lst = pt_chn;
      }
    }

  return (name);
  }
