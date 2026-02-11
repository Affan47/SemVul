elementRuleAdvance(const NodePtr &node,
				        Pattern::MatchContext &context,
				        Messenger &mgr,
				        Specificity &specificity,
				        const Vector<const ElementRule *> &vec)
{
  size_t &i = specificity.nextRuleIndex_;
  if (specificity.ruleType_ != constructionRule) {
    ++i;
    return;
  }
  size_t hit = i;
  do {
    ++i;
    if (i >= vec.size()
	|| vec[hit]->ElementRule::compareSpecificity(*vec[i]) != 0)
      return;
  } while (!(vec[i]->trivial() || vec[i]->matches(node, context)));

  const LocNode *lnp;
  Location nodeLoc;
  if ((lnp = LocNode::convert(node)) != 0
      && lnp->getLocation(nodeLoc) == accessOK)
    mgr.setNextLocation(nodeLoc);
  mgr.message(InterpreterMessages::ambiguousMatch);
  do {
    ++i;
  } while (i < vec.size()
           && vec[hit]->ElementRule::compareSpecificity(*vec[i]) == 0);
}
