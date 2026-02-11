__free_iterator(vpiHandle ihref)
{
 register int32 hi;
 register struct h_t *hp, *hp2;
 register struct hrec_t *hrp;
 struct pviter_t *iterp;

 hp = (struct h_t *) ihref;
 hrp = hp->hrec;

 if (hrp->htyp != vpiIterator) __vpi_terr(__FILE__, __LINE__);


 iterp = hrp->hu.hiterp;

 for (hi = 0; hi < iterp->numhs; hi++)
  {
   hp2 = &(iterp->scanhtab[hi]);


   hp2->hrec->in_iter = FALSE;
  }


 __my_free((char *) iterp, sizeof(struct pviter_t));
 __free_hp(hp);
}
