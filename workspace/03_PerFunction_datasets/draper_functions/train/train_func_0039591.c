onStandingOrderDeleteRequest(const aqb_AccountInfo *acc, const abt_standingOrderInfo *da)
{

	if (this->isStandingOrderInOutbox(da)) return;
	if (this->isStandingOrderOutdated(acc, da)) return;

	this->jobctrl->addDeleteStandingOrder(acc, da->getTransaction());
}
