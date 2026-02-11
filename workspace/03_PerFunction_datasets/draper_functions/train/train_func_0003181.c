accum_numvec(StringAccum &sa, const NumVector &nv, bool executable)
{
    char open = (executable ? '{' : '[');
    for (int i = 0; i < nv.size(); i++)
	sa << (i ? ' ' : open) << nv[i];
    sa << (executable ? '}' : ']');
}
