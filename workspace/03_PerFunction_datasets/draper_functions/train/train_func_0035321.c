run(int lower_to)
{
    if (lower_to < 0)
	lower_to = _nsubrs;
    if (lower_to < _save_count) {
	_errh->warning("reducing %s to minimum number of subroutines (%d)",
		       _font->font_name().c_str(), _save_count - _nonexist_count);
	lower_to = _save_count;
    }
    int to_remove = _nsubrs - _nonexist_count - lower_to;
    if (to_remove < 0)
	to_remove = 0;


    Vector<int> permute;
    for (int i = 0; i < _nsubrs; i++)
	permute.push_back(i);


    sort_keys = &_cost;
    qsort(&permute[0], _nsubrs, sizeof(int), sort_permute_compare);


    int removed = 0;
    for (int i = 0; i < _nsubrs; i++) {
	int p = permute[i];
	if (_renumbering[p] == REMOVABLE && removed < to_remove) {
	    _renumbering[p] = DEAD;
	    removed++;
	}
    }


    int renumber_pos = 0;
    for (int i = 0; i < _nsubrs; i++)
	if (_renumbering[i] == REMOVABLE) {
	    while (_renumbering[renumber_pos] >= 0)
		renumber_pos++;
	    _renumbering[i] = renumber_pos++;
	}
    SubrExpander rem0;
    rem0.set_renumbering(&_renumbering);


    for (int i = 0; i < _nsubrs; i++) {
	Type1Subr *s = _font->subr_x(i);
	if (s && _renumbering[i] >= 0)
	    rem0.run(_font, s->t1cs());
    }
    for (int i = 0; i < _font->nglyphs(); i++)
	if (Type1Subr *g = _font->glyph_x(i))
	    rem0.run(_font, g->t1cs());


    _font->renumber_subrs(_renumbering);

    return true;
}
