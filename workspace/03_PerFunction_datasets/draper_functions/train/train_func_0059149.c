GTextInfoGetMaxWidth(GWindow base,GTextInfo **ti,FontInstance *font) {
    int width=0, temp;
    int i;

    for ( i=0; ti[i]->text!=NULL || ti[i]->image!=NULL; ++i ) {
	if (( temp= GTextInfoGetWidth(base,ti[i],font))>width )
	    width = temp;
    }
return( width );
}
