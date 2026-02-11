median() {

	KNumber result = KNumber::Zero;
	size_t index;

	unsigned int bound = count();

	if (bound == 0) {
		error_flag_ = true;
		return KNumber::Zero;
	}

	if (bound == 1)
		return data_.at(0);


	QVector<KNumber> tmp_data(data_);
	qSort(tmp_data);

	if (bound & 1) {
		index = (bound - 1) / 2 + 1;
		result =  tmp_data.at(index - 1);
	} else {
		index = bound / 2;
		result = ((tmp_data.at(index - 1)) + (tmp_data.at(index))) / KNumber(2);
	}

	return result;
}
