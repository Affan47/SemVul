isStrArg(int n) const
{
    return n < _nargs && dynamic_cast<const SeExprStrNode*>(child(n)) != 0;
}
