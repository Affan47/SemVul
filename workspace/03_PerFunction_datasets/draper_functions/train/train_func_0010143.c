SFIsSomethingBuildable(SplineFont *sf,SplineChar *sc, int layer, int onlyaccents) {
    int unicodeenc = sc->unicodeenc;

    if ( onlyaccents &&
	    (unicodeenc==0x1fbd || unicodeenc==0x1fbe || unicodeenc==0x1fbf ||
	     unicodeenc==0x1fef || unicodeenc==0x1ffd || unicodeenc==0x1ffe))
return( false );

    if ((unicodeenc <= 0xffff && iszerowidth(unicodeenc)) ||
	    (unicodeenc>=0x2000 && unicodeenc<=0x2015 ))
return( !onlyaccents );

    if ( SFIsCompositBuildable(sf,unicodeenc,sc,layer))
return( !onlyaccents || hascomposing(sf,sc->unicodeenc,sc) );

    if ( !onlyaccents && SCMakeDotless(sf,sc,layer,NULL,false,false))
return( true );

return( SFIsRotatable(sf,sc,layer));
}
