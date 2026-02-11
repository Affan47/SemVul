sortcircuit( ptfig, df )
lofig_list	*ptfig;
FILE		*df;
{
  char          *vdd, *vss;
  locon_list	*scancon;
  ptype_list    *pt;
  int            colonne;
  char           v[1024];

  cherche_alim( ptfig, &vdd, &vss );


  sprintf( v, "\n.subckt %s ", ptfig->NAME );
  colonne = strlen( v );

  tooutput( df, v );

  pt = getptype( ptfig->USER, PH_INTERF );
  if( pt )
    colonne = sortconnecteur_ordre( df,
                                    (chain_list*)(pt->DATA),
                                    ptfig->LOCON,
                                    colonne
                                  );
  else
    for( scancon = ptfig->LOCON ; scancon ; scancon = scancon->NEXT )
      colonne = sortconnecteur( df, scancon, colonne );

  tooutput( df,"\n" );

  if( SPI_NAMEDNODES == FALSE ) {
    sortnet( ptfig, df );
  }

  sortinstance( ptfig, df );
  sorttransistormos( ptfig, df, vss, vdd);

  sort_locap(ptfig,df)  ;
  sort_lores(ptfig,df)  ;
  sort_loself(ptfig,df) ;

  sortrcn( ptfig, df, vss );

  tooutput( df, ".ends %s\n\n", ptfig->NAME );
}
