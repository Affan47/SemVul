set_numvec_vec(const Vector<NumVector> &nv)
{
    StringAccum sa;
    sa << '[';
    for (int i = 0; i < nv.size(); i++)
	accum_numvec(sa, nv[i], false);
    sa << ']';
    set_val(sa);
}
