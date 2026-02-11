get_pair_id1(CELL *cell, RENSETU_PAIR *pair)
{
     int i, j;
     CELL *cell_p;

     pair->hinsi  = 0;
     pair->bunrui = 0;
     pair->type   = 0;
     pair->form   = 0;
     pair->goi    = NULL;

     if ( !Null(cell_p = car(cell) ) )
       pair->hinsi = get_hinsi_id(_Atom(cell_p));
     else return;

     if ( !Null(cell_p = car(cdr(cell)) ) )
       pair->bunrui = get_bunrui_id(_Atom(cell_p), pair->hinsi);
     else return;

     if ( !Null(cell_p = car(cdr(cdr(cell))) ) )
       pair->type = get_type_id(_Atom(cell_p));
     else return;

     if ( !Null(cell_p = car(cdr(cdr(cdr(cell)))) ) )
       pair->form = get_form_id(_Atom(cell_p), pair->type);
     else return;

     if ( !Null(cell_p = car(cdr(cdr(cdr(cdr(cell))))) ) ) {
	 pair->goi = (U_CHAR *)my_alloc(sizeof(U_CHAR) * MIDASI_MAX );
	 strcpy(pair->goi, _Atom(cell_p));
     }
}
