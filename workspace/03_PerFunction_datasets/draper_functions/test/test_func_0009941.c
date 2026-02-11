debugRule()
{
    for (FWObject::iterator i=source_ruleset->begin();
         i!=source_ruleset->end(); i++)
    {
	Rule *rule = Rule::cast( *i );
        if (rule == NULL) continue;
        if (rule_debug_on && rule->getPosition()==debug_rule )
        {
            info(debugPrintRule(rule));
            info("\n");
        }
    }
}
