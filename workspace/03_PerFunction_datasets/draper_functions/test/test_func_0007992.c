isSimilar( const string& tag, const string& cgnTag ){

  return
    tag == cgnTag ||
    similar( tag, cgnTag, "hulpofkopp" ) ||
    similar( tag, cgnTag, "neut,zelfst" ) ||
    similar( tag, cgnTag, "rang,bep,zelfst,onverv" ) ||
    similar( tag, cgnTag, "stell,onverv" ) ||
    similar( tag, cgnTag, "hoofd,prenom" ) ||
    similar( tag, cgnTag, "soort,ev" ) ||
    similar( tag, cgnTag, "ev,neut" ) ||
    similar( tag, cgnTag, "inf" ) ||
    similar( tag, cgnTag, "zelfst" ) ||
    similar( tag, cgnTag, "voorinf" ) ||
    similar( tag, cgnTag, "verldw,onverv" ) ||
    similar( tag, cgnTag, "ott,3,ev" ) ||
    similar( tag, cgnTag, "ott,2,ev" ) ||
    similar( tag, cgnTag, "ott,1,ev" ) ||
    similar( tag, cgnTag, "ott,1of2of3,mv" ) ||
    similar( tag, cgnTag, "ott,1of2of3,ev" ) ||
    similar( tag, cgnTag, "ovt,1of2of3,mv" ) ||
    similar( tag, cgnTag, "ovt,1of2of3,ev" ) ||
    similar( tag, cgnTag, "ovt,3,ev" ) ||
    similar( tag, cgnTag, "ovt,2,ev" ) ||
    similar( tag, cgnTag, "ovt,1,ev" );
}
