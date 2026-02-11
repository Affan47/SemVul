addRules(RuleChain& rules) {
    RuleChain *newRule = new RuleChain(rules);
    this->mRules=newRule;
    newRule->setRepeatLimit();
}
