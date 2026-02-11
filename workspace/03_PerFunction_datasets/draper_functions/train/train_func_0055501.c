write_char_metric_data(GlyphIndex gi, int e) const
{
    if (e >= -1 && e < 256)
	fprintf(_f, "C %d ;", e);
    else
	fprintf(_f, "CH <%04X> ;", e);

    double w = _m->wd(gi);
    if (KNOWN(w))
	fprintf(_f, " WX %.8g ;", w);
    else
	w = 0;

    fprintf(_f, " N %s ;", _m->name(gi).c_str());

    if (KNOWN(_m->lf(gi)))
	fprintf(_f, " B %.8g %.8g %.8g %.8g ;",
		_m->lf(gi), _m->bt(gi), _m->rt(gi), _m->tp(gi));


    PairProgram &pairp = *_m->pair_program();
    PairOpIndex opi = pairp.find_left(gi);
    while (opi >= 0) {
	const PairOp &op = pairp.op(opi);
	if (op.is_lig()) {
	    if (op.lig_kind() == opLigSimple)
		fprintf(_f, " L %s %s ;",
			_m->name( op.right() ).c_str(),
			_m->name( op.result() ).c_str());


	}
	opi = op.next_left();
    }

    fputc('\n', _f);
}
