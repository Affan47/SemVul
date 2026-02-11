GTextInfoGetMaxHeight(GWindow base,GTextInfo **ti,FontInstance *font,int *allsame) {
    int height=0, temp, same=1;
    int i;

    for ( i=0; ti[i]->text!=NULL || ti[i]->image!=NULL; ++i ) {
	temp= GTextInfoGetHeight(base,ti[i],font);
	if ( height!=0 && height!=temp )
	    same = 0;
	if ( height<temp )
	    height = temp;
    }
    *allsame = same;
return( height );
}
