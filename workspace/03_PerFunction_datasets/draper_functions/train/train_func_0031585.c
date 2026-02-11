SplineCharQuickTop(SplineChar *sc,int layer) {
    RefChar *ref;
    real max, temp;

    max = SplineSetQuickTop(sc->layers[layer].splines);
    for ( ref = sc->layers[layer].refs; ref!=NULL; ref = ref->next )
	if ( (temp =SplineSetQuickTop(ref->layers[0].splines))>max )
	    max = temp;
return( max );
}
