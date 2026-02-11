AfficheTotal ( void )
{
    int i ;
    float Total = 0 ;

    for ( i = 0 ; i < NBR_SOMMET ; i++ )
		Total += Matrice_Conso [ 0 ][ i ] ;

	CYAN
	printf ( "\nFlot total : %.2f\n\n", Total ) ;
	DEFAULT_COLOR
}
