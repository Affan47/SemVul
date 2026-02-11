nodeListRest(EvalContext &context, Interpreter &interp)
{
  NodeListPtr nl;
  if (nodeList_->rest(nl) == accessOK)
    return new (interp) NodeListPtrNodeListObj(nl);
  else
    return interp.makeEmptyNodeList();
}
