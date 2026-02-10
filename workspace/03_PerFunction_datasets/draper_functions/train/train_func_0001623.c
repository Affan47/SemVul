seg_coda_ctype(const cst_item *seg, const char *ctype)
{
    const cst_item *s;
    const cst_phoneset *ps = item_phoneset(seg);

    for (s=item_last_daughter(item_parent(item_as(seg,"SylStructure")));
	 s;
	 s=item_prev(s))
    {
	if (cst_streq("+",phone_feature_string(ps,item_feat_string(s,"name"),
					       "vc")))
	    return VAL_STRING_0;
	if (cst_streq(ctype,phone_feature_string(ps,item_feat_string(s,"name"),
					       "ctype")))
	    return VAL_STRING_1;
    }

    return VAL_STRING_0;
}
