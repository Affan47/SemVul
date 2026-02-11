has_call(Subr *s) const
{
    for (int i = 0; i < _calls.size(); i++)
	if (_calls[i] == s)
	    return true;
    return false;
}
