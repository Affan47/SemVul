ssyl_out(const cst_item *syl)
{

    const cst_item *ss,*p,*fs;
    int c;

    ss = item_as(syl,"Syllable");

    fs = path_to_item(syl,"R:SylStructure.parent.R:Phrase.parent.daughtern.R:SylStructure.daughtern");

    for (c=0, p=item_next(ss);
	 p && (c < CST_CONST_INT_MAX);
	 p=item_next(p))
    {
	if (cst_streq("1",item_feat_string(p,"stress")))
	    c++;
	if (item_equal(p,fs))
	    break;
    }

    return val_string_n(c);
}
