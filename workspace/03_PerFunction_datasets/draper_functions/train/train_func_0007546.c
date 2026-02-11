cg_position_in_phrasep(const cst_item *p)
{
    float pstart, pend, phrasenumber;
    float x;
    #define CG_FRAME_SHIFT 0.005

    pstart = ffeature_float(p,"R:mcep_link.parent.R:segstate.parent.R:SylStructure.parent.parent.R:Phrase.parent.daughter1.R:SylStructure.daughter1.daughter1.R:Segment.p.end");
    pend = ffeature_float(p,"R:mcep_link.parent.R:segstate.parent.R:SylStructure.parent.parent.R:Phrase.parent.daughtern.R:SylStructure.daughtern.daughtern.R:Segment.end");
    phrasenumber = ffeature_float(p,"R:mcep_link.parent.R:segstate.parent.R:SylStructure.parent.parent.R:Phrase.parent.lisp_cg_find_phrase_number");
    if ((pend - pstart) == 0.0)
        return float_val(-1.0);
    else
    {
        x = phrasenumber +
            ((CG_FRAME_SHIFT*item_feat_float(p,"frame_number"))-pstart) /
            (pend - pstart);
        return float_val(x);
    }
}
