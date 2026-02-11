bld_load_iter(struct h_t *hp)
{
 register int32 iti;
 int32 iti2;
 struct h_t *ihp, *hp2;
 vpiHandle ihref;
 struct pviter_t *iterp;

 __acc_vpi_erroff = TRUE;
 ihref = vpi_iterate(vpiLoad, (vpiHandle) hp);
 if (__my_vpi_chk_error())
  {
   __acc_err(1983, "acc_next_load error finding first %s",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 if (ihref == NULL) return(NULL);
 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;


 for (iti = iti2 = 0; iti < iterp->numhs; iti++)
  {
   hp2 = &(iterp->scanhtab[iti]);
   if (hp2->hrec->htyp != vpiPrimTerm) continue;

   if (iti2 >= __aithtsiz) __grow_acc_htab(1);

   __aithtab[iti2] = *hp2;
   __aithrectab[iti2] = *(hp2->hrec);

   __aithtab[iti2].hrec = &(__aithrectab[iti2]);
   iti2++;
  }


 acc_internal_itfree(ihp);
 if (iti2 == 0) return(NULL);

 iterp = __alloc_iter(iti2, &ihref);

 memcpy(iterp->scanhtab, __aithtab, iti2*sizeof(struct h_t));
 memcpy(iterp->ihrectab, __aithrectab, iti2*sizeof(struct hrec_t));

 for (iti = 0; iti < iti2; iti++)
  {
   iterp->scanhtab[iti].hrec = &(iterp->ihrectab[iti]);
  }
 return(ihref);
}
