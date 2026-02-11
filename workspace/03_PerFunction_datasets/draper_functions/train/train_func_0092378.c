nodeListFirst(EvalContext &, Interpreter &)
{
  if (!nodeList_)
    nodeList_ = namedNodeList_->nodeList();
  NodePtr nd;
  if (nodeList_->first(nd) == accessOK)
    return nd;
  else
    return NodePtr();
}
