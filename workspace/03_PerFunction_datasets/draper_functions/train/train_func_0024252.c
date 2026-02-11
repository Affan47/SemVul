MarqueSommet ( int i, int vientDe, int Plus, int OPTIONS )
{
	if ( OPTIONS & VERB )
		printf ( "\n\tMarque \033[0;32m%2s\033[0;m venant de \033[1;32m%2s\033[0;m" , NomSommet [ i ], NomSommet [ vientDe ] ) ;
	Sommet [ i ] = vientDe ;
	SommetPlus [ i ] = Plus ;
}
