is_true_predicate (tree cond)
{
  return (cond == NULL_TREE
	  || cond == boolean_true_node
	  || integer_onep (cond));
}
