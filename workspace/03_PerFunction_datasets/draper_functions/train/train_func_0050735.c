typeMDo(l,e)
Int l;
Cell e; {
    String fixLib     = "Control.Monad.Fix";
    String fixClass   = "MonadFix";

    if( !classMonadRec ) {
	ERRMSG(0) "%s class not defined", fixClass ETHEN
        ERRTEXT   "\n*** Possible cause: \"%s\" module not imported", fixLib
	EEND;
    }

    predMonadRec = ap(classMonadRec,aVar);


    typeRecursiveDo(l,e);
}
