block(const QString& target)
{
	block_targets_.push_back(target);
	if (!block_waiting_) {
		block_waiting_ = true;
		connect(this,SIGNAL(defaultListAvailable(const PrivacyList&)),SLOT(block_getDefaultList_success(const PrivacyList&)));
		connect(this,SIGNAL(defaultListError()),SLOT(block_getDefaultList_error()));
		getDefaultList();
	}
}
