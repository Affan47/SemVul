processNext()
{
    NATRule *rule = getNext(); if (rule==NULL) return false;
    RuleElementItfInb *itf = rule->getItfInb();
    compiler->expandGroupsInRuleElement(itf);
    tmp_queue.push_back(rule);
    return true;
}
