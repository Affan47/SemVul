optimize(unsigned sort_stopper)
{

    bubble_sort_and_exprs(sort_stopper);


    {
	DominatorOptimizer dom(this);
	for (int i = 0; i < _insn.size(); i++)
	    dom.run(i);

    }
    combine_compatible_states();
    remove_unused_states();


    if (_insn.size() == 0 && _output_everything < 0)
	_output_everything = -Classification::j_never;
    else if (_output_everything >= 0)
	_insn.clear();


    _safe_length = 0;
    for (int i = 0; i < _insn.size(); i++) {
	unsigned req_len = _insn[i].required_length();
	if (req_len > _safe_length)
	    _safe_length = req_len;
    }
    _safe_length -= _align_offset;


}
