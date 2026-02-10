FBottomTransform(SplineChar *sc,int layer,ItalicInfo *ii) {
    if ( ii->f_rotate_top )
	FBottomFromTop(sc,layer,ii);
    else
	FBottomGrows(sc,layer,ii);
}
