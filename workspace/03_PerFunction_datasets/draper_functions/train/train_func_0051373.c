transformExtended() {
	uint32 a   = numAtoms();
	if (incData_) {


		incData_->startAux_ = (uint32)atoms_.size();
	}
	PrgRuleTransform tm;
	for (RuleList::size_type i = 0; i != extended_.size(); ++i) {
		incTr(extended_[i]->type(), tm.transform(*this, *extended_[i]));
		delete extended_[i];
	}
	extended_.clear();
	incTrAux(numAtoms() - a);
}
