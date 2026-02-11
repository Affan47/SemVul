read_class(FILE *fp)
{
     CELL       *cell1, *cell2;
     int        i, j;
     int 	katuyou_flag = 0;

     LineNo = 1;
     i = 1;
     while (! s_feof(fp)) {
	  j = 0;
          LineNoForError = LineNo;

          cell1 = s_read(fp);

	  if ( !Null(cell2 = car(cell1)) ) {
	       Class[i][j].id = (U_CHAR *)
		 my_alloc((sizeof(U_CHAR)*strlen(_Atom(car(cell2)))) + 1);
               strcpy(Class[i][j].id, _Atom(car(cell2)));
	       if ( !Null(cdr(cell2)) ) {
		    katuyou_flag = 1;
		    Class[i][j].kt = TRUE;
	       } else
		 katuyou_flag = 0;
               cell1 = car(cdr(cell1));
	       j++;
	  } else {
	       error_in_grammar(PARSE_ERROR, LineNo);
	  }

          while (!Null(cell2 = car(cell1))) {
               Class[i][j].id = (U_CHAR *)
                    my_alloc((sizeof(U_CHAR)*strlen(_Atom(car(cell2)))) + 1);
	       strcpy(Class[i][j].id, _Atom(car(cell2)));

	       if ( katuyou_flag || !Null(cdr(cell2)) )
		 Class[i][j].kt = TRUE;

               cell1 = cdr(cell1);
	       j++;
	       if ( j >= CLASSIFY_NO ) error_in_grammar(BUNRUI_ERROR, LineNo);
          }
          i++;
	  if ( i >= CLASSIFY_NO ) error_in_grammar(HINSI_ERROR, LineNo);
     }
}
