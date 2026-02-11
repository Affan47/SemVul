DAcpy(DynArray *dest, DynArray *orig)
{
     int i;

     DAsetTop(dest, 0);
     dest->newfn = orig->newfn;
     dest->initfn = orig->initfn;
     dest->destroyfn = orig->destroyfn;
     dest->copyfn = dest->copyfn;

     for (i=0; i<DAgetTop(orig); i++) {
	  DApush(dest, DAgetEntry(orig,i));
     }
}
