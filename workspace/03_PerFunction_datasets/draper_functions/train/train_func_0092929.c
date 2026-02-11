GImageNameFColour(Color col) {
    int i;

    col &=0xffffff;
    for ( i=0; predefn[i].name!=NULL; ++i )
	if ( col == predefn[i].value )
return( predefn[i].name );

return(NULL);
}
