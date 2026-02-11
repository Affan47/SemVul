MR_nameToRuleBlk(char *name)
#else
Junction *MR_nameToRuleBlk(name)
  char  *name;
#endif
{
    RuleEntry *q;

    require (RulePtr != NULL,"MR_nameToRule: RulePtr not initialized");

    if (name == NULL) return NULL;

    q = (RuleEntry *) hash_get(Rname,name);

	if ( q == NULL ) {
      return NULL;
    } else {
      return RulePtr[q->rulenum];
    };
}
