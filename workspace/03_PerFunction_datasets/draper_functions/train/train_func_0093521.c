integerPart() const {

	KNumber x(*this);

	if(detail::knumber_integer *const p = dynamic_cast<detail::knumber_integer *>(value_)) {

		Q_UNUSED(p);
	} else if(detail::knumber_float *const p = dynamic_cast<detail::knumber_float *>(value_)) {
		detail::knumber_base *v = new detail::knumber_integer(p);
		qSwap(v, x.value_);
		delete v;
	} else if(detail::knumber_fraction *const p = dynamic_cast<detail::knumber_fraction *>(value_)) {
		detail::knumber_base *v = new detail::knumber_integer(p);
		qSwap(v, x.value_);
		delete v;
	} else if(detail::knumber_error *const p = dynamic_cast<detail::knumber_error *>(value_)) {

		Q_UNUSED(p);
	} else {
		Q_ASSERT(0);
	}

	return x;
}
