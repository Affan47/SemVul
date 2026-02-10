getTarget()
{
    if (_withStack.empty()) {
        return getObject(env.target());
    }
    return _withStack.back().object();
}
