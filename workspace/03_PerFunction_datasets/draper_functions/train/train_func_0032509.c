equalRuleLocks(RuleLock *rlock1, RuleLock *rlock2)
{
	int			i;


	if (rlock1 != NULL)
	{
		if (rlock2 == NULL)
			return false;
		if (rlock1->numLocks != rlock2->numLocks)
			return false;
		for (i = 0; i < rlock1->numLocks; i++)
		{
			RewriteRule *rule1 = rlock1->rules[i];
			RewriteRule *rule2 = rlock2->rules[i];

			if (rule1->ruleId != rule2->ruleId)
				return false;
			if (rule1->event != rule2->event)
				return false;
			if (rule1->enabled != rule2->enabled)
				return false;
			if (rule1->isInstead != rule2->isInstead)
				return false;
			if (!equal(rule1->qual, rule2->qual))
				return false;
			if (!equal(rule1->actions, rule2->actions))
				return false;
		}
	}
	else if (rlock2 != NULL)
		return false;
	return true;
}
