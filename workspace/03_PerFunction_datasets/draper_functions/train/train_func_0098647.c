rd_edges(int32 *edge)
{
 char s1[RECLEN];
 byte etmp, e1;

 *edge = etmp = NOEDGE;
 __letendnum_state = TRUE;
 for (;;)
  {
   strcpy(s1, "");
   for (;;)
    {
     __get_vtok();
     switch ((byte) __toktyp) {
      case COMMA: case RSB: goto got_pair;
      case ID: strcat(s1, __token); break;
      case NUMBER: strcat(s1, __numtoken); break;
      default:
       __pv_ferr(1284, "edge list edge value pair expected - %s read",
        __prt_vtok());
       __letendnum_state = FALSE;
       return(FALSE);
      }
    }
got_pair:
   if (strlen(s1) > 2)
    {
bad_edge:
     __pv_ferr(1286, "edge list element %s illegal", s1);
     continue;
    }
   switch (s1[0]) {
    case '0':
     if (s1[1] == '1') e1 = EDGE01;
     else if (s1[1] == 'x') e1 = EDGE0X;
     else goto bad_edge;
     break;
    case '1':
     if (s1[1] == '0') e1 = EDGE10;
     else if (s1[1] == 'x') e1 = EDGE1X;
     else goto bad_edge;
     break;
    case 'x':
     if (s1[1] == '0') e1 = EDGEX0;
     else if (s1[1] == '1') e1 = EDGEX1;
     else goto bad_edge;
     break;
    default: goto bad_edge;
   }
   if ((etmp & e1) != 0)
    __pv_fwarn(577, "edge %s repeated in edge list", s1);
   else etmp |= e1;

   if (__toktyp == RSB) break;
  }
 __letendnum_state = FALSE;
 *edge = etmp;
 return(TRUE);
}
