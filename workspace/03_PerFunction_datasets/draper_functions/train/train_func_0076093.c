InitLibrary ( StructInitInfo * module )
{
 Obj func1;
 Obj body1;


 UpdateCopyFopyInfo();


 G_IS__FUNCTION = GVarName( "IS_FUNCTION" );
 G_ADD__LIST = GVarName( "ADD_LIST" );
 G_Error = GVarName( "Error" );
 G_IS__IDENTICAL__OBJ = GVarName( "IS_IDENTICAL_OBJ" );
 G_AND__FLAGS = GVarName( "AND_FLAGS" );
 G_HASH__FLAGS = GVarName( "HASH_FLAGS" );
 G_IS__SUBSET__FLAGS = GVarName( "IS_SUBSET_FLAGS" );
 G_TRUES__FLAGS = GVarName( "TRUES_FLAGS" );
 G_FLAGS__FILTER = GVarName( "FLAGS_FILTER" );
 G_LEN__LIST = GVarName( "LEN_LIST" );
 G_HIDDEN__IMPS = GVarName( "HIDDEN_IMPS" );
 G_WITH__HIDDEN__IMPS__FLAGS__CACHE = GVarName( "WITH_HIDDEN_IMPS_FLAGS_CACHE" );
 G_WITH__HIDDEN__IMPS__FLAGS__COUNT = GVarName( "WITH_HIDDEN_IMPS_FLAGS_COUNT" );
 G_WITH__HIDDEN__IMPS__FLAGS__CACHE__MISS = GVarName( "WITH_HIDDEN_IMPS_FLAGS_CACHE_MISS" );
 G_WITH__HIDDEN__IMPS__FLAGS__CACHE__HIT = GVarName( "WITH_HIDDEN_IMPS_FLAGS_CACHE_HIT" );
 G_CLEAR__HIDDEN__IMP__CACHE = GVarName( "CLEAR_HIDDEN_IMP_CACHE" );
 G_BIND__GLOBAL = GVarName( "BIND_GLOBAL" );
 G_IMPLICATIONS = GVarName( "IMPLICATIONS" );
 G_WITH__IMPS__FLAGS__CACHE = GVarName( "WITH_IMPS_FLAGS_CACHE" );
 G_WITH__IMPS__FLAGS__COUNT = GVarName( "WITH_IMPS_FLAGS_COUNT" );
 G_WITH__IMPS__FLAGS__CACHE__HIT = GVarName( "WITH_IMPS_FLAGS_CACHE_HIT" );
 G_WITH__IMPS__FLAGS__CACHE__MISS = GVarName( "WITH_IMPS_FLAGS_CACHE_MISS" );
 G_CLEAR__IMP__CACHE = GVarName( "CLEAR_IMP_CACHE" );
 G_UNBIND__GLOBAL = GVarName( "UNBIND_GLOBAL" );
 G_WITH__HIDDEN__IMPS__FLAGS = GVarName( "WITH_HIDDEN_IMPS_FLAGS" );
 G_RANK__FILTERS = GVarName( "RANK_FILTERS" );
 G_RankFilter = GVarName( "RankFilter" );
 G_RANK__FILTER = GVarName( "RANK_FILTER" );
 G_RANK__FILTER__LIST__CURRENT = GVarName( "RANK_FILTER_LIST_CURRENT" );
 G_RANK__FILTER__LIST = GVarName( "RANK_FILTER_LIST" );
 G_RANK__FILTER__COUNT = GVarName( "RANK_FILTER_COUNT" );


 C_NEW_STRING( DefaultName, 14, "local function" )
 C_NEW_STRING( FileName, 21, "GAPROOT/lib/filter1.g" )
 NameFunc[1] = DefaultName;
 NamsFunc[1] = 0;
 NargFunc[1] = 0;
 NameFunc[2] = DefaultName;
 NamsFunc[2] = 0;
 NargFunc[2] = 1;
 NameFunc[3] = DefaultName;
 NamsFunc[3] = 0;
 NargFunc[3] = 1;
 NameFunc[4] = DefaultName;
 NamsFunc[4] = 0;
 NargFunc[4] = 0;
 NameFunc[5] = DefaultName;
 NamsFunc[5] = 0;
 NargFunc[5] = 1;
 NameFunc[6] = DefaultName;
 NamsFunc[6] = 0;
 NargFunc[6] = 1;
 NameFunc[7] = DefaultName;
 NamsFunc[7] = 0;
 NargFunc[7] = 1;
 NameFunc[8] = DefaultName;
 NamsFunc[8] = 0;
 NargFunc[8] = 1;


 func1 = NewFunction(NameFunc[1],NargFunc[1],NamsFunc[1],HdlrFunc1);
 ENVI_FUNC( func1 ) = CurrLVars;
 CHANGED_BAG( CurrLVars );
 body1 = NewBag( T_BODY, NUMBER_HEADER_ITEMS_BODY*sizeof(Obj));
 BODY_FUNC( func1 ) = body1;
 CHANGED_BAG( func1 );
 CALL_0ARGS( func1 );


 return 0;

}
