_make_rensetu_tbl1(CELL *cell1, int *cnt)
{
     int                i, flag;
     RENSETU_PAIR       r_pair;
     CELL               *cell11;

     while (!Null(cell11 = car(cell1))) {
	  if ( !Null(car(cdr(cdr(cdr(cdr(cell11)))))) ) {
	       get_pair_id1(cell11, &r_pair);

	       flag = 1;
	       for ( i=1; i<*cnt; i++ )
		   if ( pair_match1(&rensetu_tbl[i], &r_pair) ) {
		       flag = 0;
		       break;
		   }

	       if ( flag && r_pair.type )
		 for ( i=1; Form[r_pair.type][i].name != NULL; i++ ) {
		      rensetu_tbl[*cnt].hinsi  = r_pair.hinsi;
		      rensetu_tbl[*cnt].bunrui = r_pair.bunrui;
		      rensetu_tbl[*cnt].type   = r_pair.type;
		      rensetu_tbl[*cnt].form   = i;
		      rensetu_tbl[*cnt].goi    = r_pair.goi;
		      (*cnt)++;
		      if ( *cnt >= REN_TBL_MAX )
			error(OtherError, "Not enough size for table", EOA);
		 }
	       else if ( flag ) {
		    rensetu_tbl[*cnt].hinsi  = r_pair.hinsi;
		    rensetu_tbl[*cnt].bunrui = r_pair.bunrui;
		    rensetu_tbl[*cnt].type   = r_pair.type;
		    rensetu_tbl[*cnt].form   = r_pair.form;
		    rensetu_tbl[*cnt].goi    = r_pair.goi;
		    (*cnt)++;
		    if ( *cnt >= REN_TBL_MAX )
		      error(OtherError, "Not enough size for table", EOA);
	       }
	  }
	  cell1 = cdr(cell1);
     }
}
