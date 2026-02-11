simplifyNode(RIG_Node *node)
{
   for (Graph::EdgeIterator ei = node->outgoing(); !ei.end(); ei.next())
      simplifyEdge(node, RIG_Node::get(ei));

   for (Graph::EdgeIterator ei = node->incident(); !ei.end(); ei.next())
      simplifyEdge(node, RIG_Node::get(ei));

   DLLIST_DEL(node);
   stack.push(node->getValue()->id);

   INFO_DBG(prog->dbgFlags, REG_ALLOC, "SIMPLIFY: pushed %%%i%s\n",
            node->getValue()->id,
            (node->degree < node->degreeLimit) ? "" : "(spill)");
}
