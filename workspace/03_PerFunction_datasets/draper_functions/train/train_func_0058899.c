GMenuItemArrayMask(GMenuItem *mi) {
    int mask = 0;
    int i;

    for ( i=0; mi[i].ti.text!=NULL || mi[i].ti.image!=NULL || mi[i].ti.line; ++i ) {
	if ( mi[i].sub!=NULL )
	    mask |= GMenuItemArrayMask(mi[i].sub);
	else
	    mask |= mi[i].short_mask;
    }
return( mask );
}
