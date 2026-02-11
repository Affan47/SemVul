vhdlsavefbport( pthedfbfig, synopsys )

  fbfig_list *pthedfbfig;
  int         synopsys;
{
  char         *mode;
  char         *type_mark;
  int           left,right;
  char         *name;
  char         *bus;

  struct fbpor *ptfbpor   = 0;

  ptfbpor = pthedfbfig->BEPOR;
  if (ptfbpor != 0)
    {
    (void) fprintf (FblDriveFile,"  PORT (\n");
    pthedfbfig->BEPOR = (struct fbpor *)reverse ( (chain_list *)pthedfbfig->BEPOR);

    ptfbpor = pthedfbfig->BEPOR;
    while (ptfbpor != 0)
      {
      switch (ptfbpor->DIRECTION)
        {
        case 'I':
          mode = namealloc("IN");
          break;
        case 'O':
        case 'Z':
          mode = namealloc("OUT");
          break;
        case 'B':
        case 'T':
          mode = namealloc("INOUT");
          break;
        default :
          {
          fbl_error (69,0);
          }
        }
      ptfbpor = (fbpor_list *)fbl_vectnam(ptfbpor,&left,&right,&name,0);

      if(left != -1)
        {
        switch (ptfbpor->TYPE)
          {
            case FBH_TYPE_BIT_VEC :
            type_mark = namealloc("BIT_VECTOR");
            bus = "";
            break;
            case FBH_TYPE_WOR_VEC :
            type_mark = namealloc("WOR_VECTOR");
            bus = namealloc("BUS");
            break;
            case FBH_TYPE_MUX_VEC :
            type_mark = namealloc("MUX_VECTOR");
            bus = namealloc("BUS");
            break;
          default :
            {
            fbl_error (68,0);
            }
          }
        (void)fprintf(FblDriveFile,"  %s : %s %s(%d %s %d) %s",vhdlablname(name), mode,
                      type_mark, left, (left>=right)?"DOWNTO":"TO",right,bus);
        }
      else
        {
        switch (ptfbpor->TYPE)
          {
            case FBH_TYPE_BIT :
            type_mark = "BIT"; break;
            case FBH_TYPE_WOR_BIT :
            type_mark = "WOR_BIT BUS"; break;
            case FBH_TYPE_MUX_BIT :
            type_mark = "MUX_BIT BUS"; break;
          default :
            {
            fbl_error (68,0);
            }
          }

        (void) fprintf (FblDriveFile,"  %s : %s %s",vhdlablname(name),
                                          mode,type_mark);
        }

      if (ptfbpor->NEXT != 0)
        (void) fprintf (FblDriveFile,";\t-- %s\n",name);
      else
        (void) fprintf (FblDriveFile,"\t-- %s\n  );\n",name);

      ptfbpor = ptfbpor->NEXT;
      }

    pthedfbfig->BEPOR = (struct fbpor *)reverse ( (chain_list *)pthedfbfig->BEPOR);
    }

}
