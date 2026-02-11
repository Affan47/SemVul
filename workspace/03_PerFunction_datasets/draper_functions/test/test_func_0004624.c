mark_recs(fp, typ, num_offsets, offset, bad_recs)
struct fentry *fp;
#ifdef OptimizeType
struct typinfo *typ;
#else
unsigned int *typ;
#endif
int *num_offsets;
int *offset;
int *bad_recs;
   {
   struct par_rec *rp;
   struct type *wktyp;
   int frst_rec;

   *num_offsets = 0;
   *offset = -1;
   *bad_recs = 0;

   wktyp = get_wktyp();
   CpyTyp(n_icntyp, typ, wktyp->bits);


   frst_rec = type_array[rec_typ].frst_bit;
   for (rp = fp->rlist; rp != NULL; rp = rp->next) {
      if (bitset(wktyp->bits, frst_rec + rp->rec->rec_num)) {


         rp->mark = 1;
         clr_typ(wktyp->bits, frst_rec + rp->rec->rec_num);
         if (*offset != rp->offset) {
            *offset = rp->offset;
            *num_offsets += 1;
            }
        }
      }


   *bad_recs = has_type(wktyp->bits, rec_typ, 0);
   free_wktyp(wktyp);
   }
