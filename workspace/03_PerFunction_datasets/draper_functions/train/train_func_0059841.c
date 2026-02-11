allBases() const
{
    ExceptionList result;
    if(_base)
    {
        result = _base->allBases();
        result.push_front(_base);
    }
    return result;
}
