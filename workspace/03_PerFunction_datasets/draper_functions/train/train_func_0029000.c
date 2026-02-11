unparse(Vector<Positioning> &v) const
{
    if (_d[1] == 1) {
	int format1 = _d.u16(4);
	int format2 = _d.u16(6);
	int f2_pos = PAIRVALUE_HEADERSIZE + GposValue::size(format1);
	int pairvalue_size = f2_pos + GposValue::size(format2);
	for (Coverage::iterator i = coverage().begin(); i; i++) {
	    Data pairset = _d.offset_subtable(F1_HEADERSIZE + i.coverage_index()*F1_RECSIZE);
	    int npair = pairset.u16(0);
	    for (int j = 0; j < npair; j++) {
		Data pair = pairset.subtable(PAIRSET_HEADERSIZE + j*pairvalue_size);
		v.push_back(Positioning(Position(*i, format1, pair.subtable(PAIRVALUE_HEADERSIZE)),
					Position(pair.u16(0), format2, pair.subtable(f2_pos))));
	    }
	}
    } else {
	int format1 = _d.u16(4);
	int format2 = _d.u16(6);
	int f2_pos = GposValue::size(format1);
	int recsize = f2_pos + GposValue::size(format2);
	ClassDef class1(_d.offset_subtable(8));
	ClassDef class2(_d.offset_subtable(10));
	Coverage coverage = this->coverage();
	int nclass1 = _d.u16(12);
	int nclass2 = _d.u16(14);
	int offset = F2_HEADERSIZE;
	for (int c1 = 0; c1 < nclass1; c1++)
	    for (int c2 = 0; c2 < nclass2; c2++, offset += recsize) {
		Position p1(format1, _d.subtable(offset));
		Position p2(format2, _d.subtable(offset + f2_pos));
		if (p1 || p2) {
		    for (ClassDef::class_iterator c1i = class1.begin(c1, coverage); c1i; c1i++)
			for (ClassDef::class_iterator c2i = class2.begin(c2); c2i; c2i++)
			    v.push_back(Positioning(Position(*c1i, p1), Position(*c2i, p2)));
		}
	    }
    }
}
