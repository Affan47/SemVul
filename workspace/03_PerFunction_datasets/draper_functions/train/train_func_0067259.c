bld_inst_xmr_comptab(char *inam)
{
 register int32 ci;
 register char *chp, *chp2;
 int32 len;
 char s1[IDLEN], s2[IDLEN];


 __last_bind_comp_ndx = -1;

 for (chp = inam;;)
  {
   if (*chp == '\\')
    {
     if ((chp2 = strchr(chp, ' ')) == NULL)
      {
bad_end:
       for (ci = 0; ci <= __last_bind_comp_ndx; ci++)
        {
         __my_free(__bind_inam_comptab[ci],
          strlen(__bind_inam_comptab[ci]) + 1);
         __bind_inam_comptab[ci] = NULL;
        }
       return(TRUE);
      }

     strncpy(s1, chp, chp2 - chp);
     s1[chp2 - chp] = '\0';
     if (!chk_escid(s1)) goto bad_end;
     strcpy(s2, &(s1[1]));
     s2[chp2 - chp - 2] = '\0';
     chp++;
    }
   else
    {
     if ((chp2 = strchr(chp, '.')) == NULL)
      {
       strcpy(s2, chp);
       len = strlen(chp);
       chp = &(chp[len]);
      }
     else
      {

       strncpy(s2, chp, chp2 - chp);
       s2[chp2 - chp] = '\0';
       chp = chp2;
      }
    }

   if (++__last_bind_comp_ndx >= __siz_bind_comps) grow_bind_comps();
   __bind_inam_comptab[__last_bind_comp_ndx] = __pv_stralloc(s2);

   if (*chp == '\0') break;
   if (*chp != '.') goto bad_end;
   chp++;
  }
 return(TRUE);
}
