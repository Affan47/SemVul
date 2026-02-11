parse_scope_ref(struct itree_t **ref_itp, struct task_t **ref_tskp,
 int32 *ref_ifi, int32 *ref_lini, int32 *iref)
{
 register char *chp;
 int32 ifi, lini, maxlini;
 struct itree_t *itp;
 struct task_t *tskp;
 char *savchp, *endchp, sref[RECLEN];


 *iref = TRUE;


 if (!try_get_fillin_ref(__visp->vichp, &ifi, &lini, &savchp, &endchp))
  return(FALSE);

 if (ifi != -1)
  {
set_line_scope:
   if ((maxlini = get_lastfillin(ifi)) == -1) return(FALSE);
   if (lini > maxlini)
    {
     __ia_err(1469,
      "[file]:[line] reference line number %d too large - %s has %d lines",
      lini, __in_fils[ifi], maxlini);
     return(FALSE);
    }

   if (!fil_lin_toscope(ifi, lini, ref_itp, ref_tskp))
    {
     __ia_err(1454,
      "scope reference %s:%d illegal - line not inside any module",
      __in_fils[ifi], lini);
     return(FALSE);
    }
   *ref_ifi = ifi;
   *ref_lini = lini;

   *iref = FALSE;

   __visp->vichp = endchp;
   return(TRUE);
  }


 strncpy(sref, savchp, endchp - savchp);
 sref[endchp - savchp] = '\0';

 __visp->vichp = endchp;

 if (sref[0] == '.')
  {
   *ref_ifi = -1;
   *ref_lini = -1;
   return(local_scope_ref(sref, ref_itp, ref_tskp));
  }


 if (isdigit(sref[0]))
  {
   for (chp = sref; *chp != '\0'; chp++)
    {
     if (!isdigit(*chp))
      {
bad_lin:
       __ia_err(1452, "scope reference [line] form %s illegal format", sref);
       return(FALSE);
      }
    }
   if (sscanf(sref, "%d", &lini) != 1) goto bad_lin;
   ifi = __list_cur_ifi;
   goto set_line_scope;
  }


 __visp->vichp = savchp;


 __get_vtok();
 if (__toktyp != ID)
  {
   __ia_err(1467, "scope reference %s illegal", __prt_vtok());
   return(FALSE);
  }
 if (!get_var_scope(&itp, &tskp, iref)) return(FALSE);
 *ref_itp = itp;
 *ref_tskp = tskp;
 *ref_ifi = -1;
 *ref_lini = -1;
 return(TRUE);
}
