compare(knumber_base *rhs) {

	if(knumber_integer *const p = dynamic_cast<knumber_integer *>(rhs)) {
		if(sign() > 0) {
			return 1;
		} else {
			return -1;
		}
	} else if(knumber_float *const p = dynamic_cast<knumber_float *>(rhs)) {
		if(sign() > 0) {
			return 1;
		} else {
			return -1;
		}
	} else if(knumber_fraction *const p = dynamic_cast<knumber_fraction *>(rhs)) {
		if(sign() > 0) {
			return 1;
		} else {
			return -1;
		}
	} else if(knumber_error *const p = dynamic_cast<knumber_error *>(rhs)) {
		return sign() == p->sign();
	}

	Q_ASSERT(0);
	return 0;
}
