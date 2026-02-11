smassert(bool b, const std::string& tp, const Stringmap& m) {
	if(!b) {
		SMExcept e(tp);
		e += m;
		throw e;
	}
}
