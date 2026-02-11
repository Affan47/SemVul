flush() {
	if (g.inpath) return;
	if (g.xinline) {
		out() << "stroke" << endl;
		ps_nvec = 0;
	}
}
