Print() const
{
    if (!_stack.empty())
    {
        for (int i = _stack.size() - 1; i >= 0; --i)
        {
            LOG_ERROR << i << ": " << _stack[i] << std::endl;
        }
    }
}
