clone(vector<Node const *> const &parents) const
{
    return new AggNode(this->dim(), parents, _offsets);
}
