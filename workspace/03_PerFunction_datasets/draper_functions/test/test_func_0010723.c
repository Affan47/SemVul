S_cop_free(pTHX_ COP* cop)
{
    PERL_ARGS_ASSERT_COP_FREE;

    CopFILE_free(cop);
    if (! specialWARN(cop->cop_warnings))
	PerlMemShared_free(cop->cop_warnings);
    cophh_free(CopHINTHASH_get(cop));
}
