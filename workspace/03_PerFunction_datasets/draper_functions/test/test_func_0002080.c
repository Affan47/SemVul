negate_subtree(Vector<int> &tree, bool flip_short)
{

    int level = tree[0];
    int first = _insn.size() - 1;
    while (first >= 0 && tree[first+1] != level)
	--first;

    for (int i = first; i < _insn.size(); i++) {
	Insn &e = _insn[i];
	if (e.yes() == j_failure)
	    e.yes() = j_success;
	else if (e.yes() == j_success)
	    e.yes() = j_failure;
	if (e.no() == j_failure)
	    e.no() = j_success;
	else if (e.no() == j_success)
	    e.no() = j_failure;
	if (flip_short)
	    e.short_output = !e.short_output;
    }
}
