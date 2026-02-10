add_ligature(Code in1, Code in2, Code out)
{
    if (Ligature *l = ligature_obj(in1, in2)) {
	Char &ch = _encoding[l->out];
	if (ch.flags & Char::BUILT) {

	    for (Ligature *ll = ch.ligatures.begin(); ll != ch.ligatures.end(); ll++)
		add_ligature(out, ll->in2, ll->out);
	    repoint_ligature(in1, l, out);
	}
    } else
	new_ligature(in1, in2, out);
}
