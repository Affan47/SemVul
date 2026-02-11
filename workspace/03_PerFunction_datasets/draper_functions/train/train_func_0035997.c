Degenerate(Alignment& a, TElement*& e) {
    if (!lbElems->Empty() && rtElems->Empty()) {
	if (lbElems->OnlyOne()) {
	    e = lbElems->First()->GetElem();
	    a = TopRight;
	    return true;
	}
    } else if (lbElems->Empty() && !rtElems->Empty()) {
	if (rtElems->OnlyOne()) {
	    e = rtElems->First()->GetElem();
	    a = BottomLeft;
	    return true;
	}
    }
    return false;
}
