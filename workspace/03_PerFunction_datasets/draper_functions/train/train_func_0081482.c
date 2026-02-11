buildRulePtr( void )
#else
buildRulePtr( )
#endif
{
	int r=1;
	Junction *p  = SynDiag;
	RulePtr = (Junction **) calloc(NumRules+1, sizeof(Junction *));
	require(RulePtr!=NULL, "cannot allocate RulePtr array");

	while ( p!=NULL )
	{
		require(r<=NumRules, "too many rules???");
		RulePtr[r++] = p;
		p = (Junction *)p->p2;
	}
}
