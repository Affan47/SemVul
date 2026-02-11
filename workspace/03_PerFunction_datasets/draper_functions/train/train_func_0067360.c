getSupposedJobqueue_LastPos(int firstPos) const
{
	if (this->jobqueue->size()-1 <= firstPos) {
		return firstPos;
	}

	const AB_ACCOUNT *acc = this->jobqueue->at(firstPos)->getAbAccount();


	int lastPos = -1;


	for (int pos=firstPos+1; pos<this->jobqueue->size(); ++pos) {
		if (this->jobqueue->at(pos)->getAbAccount() != acc) {
			lastPos = pos - 1;
			break;
		}
	}


	if (lastPos == -1) {
		lastPos = this->jobqueue->size()-1;
	}


	return lastPos;
}
