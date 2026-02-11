copy_range(svector<PExpr*>* orig)
{
      svector<PExpr*>*copy = 0;

      if (orig) {
	    copy = new svector<PExpr*>(2);
	    (*copy)[0] = (*orig)[0];
	    (*copy)[1] = (*orig)[1];
      }

      return copy;
}
