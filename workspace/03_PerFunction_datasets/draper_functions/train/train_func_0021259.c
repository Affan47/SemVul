AfficheConso ( void )
{
	int i, j ;

	GREEN
	printf ( "\n" ) ;
	for ( i = 0 ; i < NBR_SOMMET ; i++ )
		printf ( "  %3s  ", NomSommet[ i ] ) ;
	DEFAULT_COLOR

	printf( "\n" );

	for ( i = 0 ; i < NBR_SOMMET ; i++ )
	{

		for ( j = 0 ; j < NBR_SOMMET ; j++ )
		{
			printf ( "\033[0;33m" );

			if ( Matrice_Max[ i ][ j ] )
			{
				if (  Matrice_Conso[ i ][ j ] == Matrice_Max[ i ][ j ]  )
					printf ( "\033[1;33m" );

				printf ( " %2.0f/%2.0f ", Matrice_Conso[ i ][ j ], Matrice_Max[ i ][ j ] );
			} else
				printf ( " ----- " );
		}
		GREEN printf ( " %3s\n", (NomSommet [ i ]) ); DEFAULT_COLOR
	}
}
