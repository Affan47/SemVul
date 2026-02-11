acc_next_scope(handle ref_scope_p, handle scope)
{
 struct h_t *hp, *hp2;
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) ref_scope_p;
 if (!validate_acc_handle("acc_next_scope", hp)) return(NULL);

 switch (hp->hrec->htyp) {
  case vpiModule: case vpiTask: case vpiFunction:
  case vpiNamedBegin: case vpiNamedFork:
   break;
  default:
   __acc_err(1741, "acc_next_scope: object %s illegal - scope object required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
 }


 if (scope == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiInternalScope, (vpiHandle) ref_scope_p);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_scope error finding first scope object");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);

   aip = alloc_aiter();

   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;


   aip->aiternxt = __aiter_tab[vpiScope];
   __aiter_tab[vpiScope] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan((vpiHandle) aip->aiter);

   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);

   return((handle) nxth);
  }

 hp2 = (struct h_t *) scope;
 if (!validate_acc_handle("acc_next_scope", hp2)) return(NULL);

 if ((aip = find_aiter_rec(__aiter_tab[vpiScope], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_scope last accPrimitive object not returned by previous acc_next_scope call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiScope, FALSE); return(NULL); }
 return((handle) nxth);
}
