unwind_lhsconcats(struct expr_t *ndp)
{
 if (__isleaf(ndp)) return;


 if (ndp->lu.x != NULL)
  {


   unwind_lhsconcats(ndp->lu.x);


  }
 if (ndp->ru.x != NULL)
  {


   unwind_lhsconcats(ndp->ru.x);


  }


 if (ndp->optyp == LCB)
  {
   register struct expr_t *ndp2;
   struct expr_t *last_ndp2, *end_ndp;

   last_ndp2 = ndp;
   for (ndp2 = ndp->ru.x; ndp2 != NULL; ndp2 = ndp2->ru.x)
    {
     struct expr_t *lop;

     lop = ndp2->lu.x;

     switch ((byte) lop->optyp) {

      case NUMBER: case ISNUMBER: case REALNUM: case ISREALNUM:
       break;
      case LCB:
       {

        last_ndp2->ru.x = lop->ru.x;

        end_ndp = __find_catend(lop);


        if (end_ndp == NULL) __misc_terr(__FILE__, __LINE__);


        end_ndp->ru.x = ndp2->ru.x;

        last_ndp2 = end_ndp;
       }
       continue;
      case CATREP:

       continue;
      }

     last_ndp2 = ndp2;
    }
  }
}
