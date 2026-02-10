awe_match_preset(SFPatchRec *rec, SFPatchRec *pat)
{
	if (rec->preset != -1 && pat->preset != -1 &&
	    rec->preset != pat->preset)
		return FALSE;
	if (rec->bank != -1 && pat->bank != -1 &&
	    rec->bank != pat->bank)
		return FALSE;
	if (rec->keynote != -1 && pat->keynote != -1 &&
	    rec->keynote != pat->keynote)
		return FALSE;
	return TRUE;
}
