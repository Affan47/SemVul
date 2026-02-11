MR_complete_set(int predDepth,set *tokensUsed,set *incomplete)
#else
void MR_complete_set(predDepth,tokensUsed,incomplete)
  int       predDepth;
  set       *tokensUsed;
  set       *incomplete;
#endif
{
    int             i;
    RuleRefNode     *ruleRef;
	set             rk2;
    set             b;
	int             k2;
    Junction        *save_MR_RuleBlkWithHalt;

    if (set_int(*incomplete) > (unsigned) predDepth) {
      return;
    };

    require(MR_PredRuleRefStack.count == MR_RuleBlkWithHaltStack.count,
                "RuleRefStack and RuleBlkWithHaltStack not same size");

    require(MR_RuleBlkWithHalt == NULL ||
         (MR_RuleBlkWithHalt->jtype == RuleBlk && MR_RuleBlkWithHalt->end->halt == TRUE),
                     "RuleBlkWithHalt has no halt set");

    save_MR_RuleBlkWithHalt=MR_RuleBlkWithHalt;

    if (MR_RuleBlkWithHalt != NULL) {
      MR_RuleBlkWithHalt->end->halt=FALSE;
    };

    for (i=MR_PredRuleRefStack.count-1; i >= 0 ; i--) {
      ruleRef=(RuleRefNode *)MR_PredRuleRefStack.data[i];
      if (ruleRef == NULL) continue;

      MR_RuleBlkWithHalt=(Junction *)MR_RuleBlkWithHaltStack.data[i];
      if (MR_RuleBlkWithHalt != NULL) MR_RuleBlkWithHalt->end->halt=TRUE;

      rk2=empty;
      b=empty;

      while ( !set_nil(*incomplete) ) {
		k2=set_int(*incomplete);
        if (k2 > predDepth) break;
		set_rm(k2,*incomplete);
        REACH(ruleRef->next,k2,&rk2,b);
		set_orin(tokensUsed,b);
		set_free(b);
      };

      if (MR_RuleBlkWithHalt != NULL) MR_RuleBlkWithHalt->end->halt=FALSE;

	  set_orin(incomplete,rk2);
      set_free(rk2);
	  if (set_int(*incomplete) > (unsigned) predDepth) break;
    };

    MR_RuleBlkWithHalt=save_MR_RuleBlkWithHalt;
    if (MR_RuleBlkWithHalt != NULL) {
      MR_RuleBlkWithHalt->end->halt=TRUE;
    };
}
