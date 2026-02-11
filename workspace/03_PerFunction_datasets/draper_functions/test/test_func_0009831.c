edialign_exclude_frg_read( char *file_name , int ***exclude_list)
{
    char exclude_file_name[ NAME_LEN ];
    FILE *fp;
    char line[ 10000 ];
    ajint i;
    ajint len;
    ajint beg1;
    ajint beg2;
    ajuint seq1;
    ajuint seq2;

    strcpy( exclude_file_name , file_name );
    strcat( exclude_file_name , ".xfr" );

    if( (fp = fopen( exclude_file_name, "r")) == NULL)
	edialign_erreur("\n\n cannot find file with excluded fragments \n\n");


    while( fgets( line , MLINE , fp ) != NULL )
    {
	if( strlen( line ) > 4 )
	{
	    sscanf(line,"%u %u %d %d %d", &seq1, &seq2, &beg1, &beg2 , &len);

	    if( seq1 > seqnum )
	    {
		printf ("\n\n exclueded fragment makes no sense!\n\n");
		printf (" wrong sequence no %u in fragment\n\n", seq1 );
		printf ("%u %u %d %d %d \n\n ", seq1, seq2, beg1, beg2 , len);
		embExitBad() ;
	    }

	    if( seq2 > seqnum )
	    {
		printf ("\n\n    excluded fragment makes no sense!\n\n");
		printf ("    wrong sequence no %u in fragment\n\n", seq2 );
		printf ("    %u %u %d %d %d \n\n", seq1, seq2, beg1, beg2,
			len );
		embExitBad() ;
	    }


	    if( beg1 + len > seqlen[ seq1 - 1 ] + 1 ){
		printf ("\n\n    excluded fragment makes no sense!\n");
		printf ("    fragment");
		printf ("     \" %d %d %d %d %d \"\n", seq1, seq2, beg1,
			beg2 , len );
		printf ("    doesn't fit into sequence %u:\n", seq1 );
		printf ("    sequence %u has length =  %d\n\n", seq1 ,
			seqlen[ seq1 - 1 ] );
		embExitBad() ;
	    }


	    for( i = 0 ; i < len ; i++ )
	    {
		exclude_list[ seq1 - 1 ][ seq2 - 1 ][ beg1 + i ] = beg2 + i ;
	    }
	}
    }

    return;
}
