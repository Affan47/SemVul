getSupposedJobqueue_NextDatedPos(int firstDatedPos,
						   int lastPos) const
{
	int wantedPos = -1;


	for (int pos=firstDatedPos; pos<=lastPos; ++pos) {
		AB_JOB_TYPE qtype = this->jobqueue->at(pos)->getAbJobType();
		if ((qtype == AB_Job_TypeCreateDatedTransfer) ||
		    (qtype == AB_Job_TypeModifyDatedTransfer) ||
		    (qtype == AB_Job_TypeDeleteDatedTransfer)) {
			continue;
		}

		wantedPos = pos;
		break;
	}


	if (wantedPos == -1) {
		wantedPos = lastPos + 1;
	}

	return wantedPos;
}
