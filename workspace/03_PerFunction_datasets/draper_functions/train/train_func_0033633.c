qcos(
#endif
    PTreeNode *pt,
    ObjStruct *os,
    int numInputs,
    Pointer *inputs,
    Pointer result,
    InvalidComponentHandle *invalids,
    InvalidComponentHandle outInvalid)
{
    register float *out = (float *) result;
    register float *in0 = (float *) inputs[0];
    int i;
    int numBasic;

    for (numBasic = 1, i = 0;
	    i < pt->metaType.rank;
	    ++i)
	numBasic *= pt->metaType.shape[i];

    numBasic *= pt->metaType.items;
#ifdef COMMENT_FMOD
    vsdiv(in0, 1, 2 * PI, out, 1, numBasic);
    vfrac(out, 1,         out, 1, numBasic);
    vsmul(out, 1, 2 * PI, out, 1, numBasic);
    for (i = 0; i < numBasic; ++i)
	if (out[i] < -PI)
	    out[i] += 2 * PI;
	else if (out[i] > PI)
	    out[i] -= 2 * PI;
#endif
    qvcos(numBasic, in0, out);

    return (OK);
}
