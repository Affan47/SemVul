compute_allotment(Allotment& a, Coord offset) const {
    Coord n = a.span();
    if (offset > 0) {
	a.span(n - offset);
	a.alignment(a.alignment() * n / a.span());
    } else {
	a.span(n + offset);
	a.alignment((a.alignment() * n + offset) / a.span());
    }
}
