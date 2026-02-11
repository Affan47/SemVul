factorial() const {
	KNumber z(*this);


	if(z > KNumber(QLatin1String("10000000000"))) {
		return PosInfinity;
	}

	z.value_ = z.value_->factorial();
	z.simplify();
	return z;
}
