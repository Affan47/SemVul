insertNodeAfterPosition(NodeImpl *node, const Position &pos)
{


    Position upstream(pos.equivalentUpstreamPosition());
    NodeImpl *cb = pos.node()->enclosingBlockFlowElement();
    if (cb == pos.node())
        appendNode(cb, node);
    else
        insertNodeAfter(node, pos.node());
}
