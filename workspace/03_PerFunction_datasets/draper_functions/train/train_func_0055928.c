visit(NodePtr node)
{
    node->accept(this, node);
}
