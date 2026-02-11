rendersOnSameLine(const Position &pos) const
{
    if (isEmpty() || pos.isEmpty())
        return false;

    if (*this == pos)
        return true;

    if (node()->enclosingBlockFlowElement() != pos.node()->enclosingBlockFlowElement())
        return false;

    RenderPosition self = RenderPosition::fromDOMPosition(*this);
    RenderPosition other = RenderPosition::fromDOMPosition(pos);
    return RenderPosition::rendersOnSameLine(self, other);
}
