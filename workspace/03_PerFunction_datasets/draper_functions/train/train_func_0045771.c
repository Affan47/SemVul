process_exceptions(Node *n) {
    ParmList *catchlist = 0;


    String *scatchlist = Getattr(n, "feature:catches");
    if (scatchlist) {
      catchlist = Swig_cparse_parms(scatchlist);
      if (catchlist) {
	Setattr(n, "catchlist", catchlist);
	mark_exception_classes(catchlist);
	Delete(catchlist);
      }
    }
    ParmList *throws = Getattr(n, "throws");
    if (throws) {

      if (!catchlist) {
	Setattr(n, "catchlist", throws);
      }
      mark_exception_classes(throws);
    }
  }
