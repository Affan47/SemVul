utl_SaveNStringWithMode (str, n, mode)

char         *str ;
unsigned int  n   ;
unsigned int  mode;

  {
  char          buf [UTL_STR__MAXLEN] ;
  char         *svd_str               = NULL;
  struct uttyp *pt_typ                ;
  unsigned int  size                  = 0   ;
  unsigned int  hsh_cod1              ;
  unsigned int  hsh_cod2              ;
  unsigned int  tab_idx               ;
  int           i                     ;


  utl_Trace ("utl_SaveNStringWithMode", UTL_FUN__IN);


  if (UTL_STRTAB == NULL)
    {
    UTL_STRTAB = (struct uttyp **)
                 utl_alloc (sizeof (struct uttyp *) * UTL_STR__TABLESIZE);

    for (i=0 ; i<UTL_STR__TABLESIZE ; i++)
      UTL_STRTAB [i] = NULL;
    }


  if (str != NULL)
    {
    if ((mode & UTL_STR__UPPER) != 0)
      {
      while (((buf [size] = str [size]) != '\0') && (size < n))
        {
        if ((buf [size] <= 'z') && (buf [size] >= 'a'))
          buf [size] = buf [size] - 'a' + 'A';

        size ++;
        }
      }

    if ((mode & UTL_STR__LOWER) != 0)
      {
      while (((buf [size] = str [size]) != '\0') && (size < n))
        {
        if ((buf [size] <= 'Z') && (buf [size] >= 'A'))
          buf [size] = buf [size] - 'A' + 'a';

        size ++;
        }
      }

    if ((mode & UTL_STR__NOP  ) != 0)
      {
      while (((buf [size] = str [size]) != '\0') && (size < n))
        size ++;
      }

    buf [size] = '\0';
    size ++;


    utl_hash2 (buf, &hsh_cod1, &hsh_cod2);


    tab_idx = hsh_cod1 % UTL_STR__TABLESIZE;
    pt_typ  = UTL_STRTAB [tab_idx];
    while (pt_typ != NULL)
      {
      if ((pt_typ->DAT2.UINT == hsh_cod2            ) &&
          (!strcmp (buf, (char *) pt_typ->DAT1.VPNT))   )
        break;
      pt_typ = pt_typ->NEXT;
      }


    if (pt_typ == NULL)
      {
      svd_str = utl_alcbyt (size);
      strcpy (svd_str, buf);

      pt_typ               = utl_adduttyp (NULL, (void *) svd_str, hsh_cod2);
      pt_typ->NEXT         = UTL_STRTAB [tab_idx];
      UTL_STRTAB [tab_idx] = pt_typ;
      }
    else
      svd_str = (char *) pt_typ->DAT1.VPNT;

    }

  utl_Trace ("utl_SaveNStringWithMode", UTL_FUN__OUT);

  return (svd_str);
  }
