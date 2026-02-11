initBase(OppBase *base, bool isPlayFirst)
{
	if (false == isPlayFirst) {
		base->nonDealerRoot  = (struct Node*)malloc(sizeof(struct Node));
		initNode(base->nonDealerRoot, strength);
		return base->nonDealerRoot;
		}
	else {
		base->dealerRoot  = (struct Node*)malloc(sizeof(struct Node));
		initNode(base->dealerRoot, prob);
		return base->dealerRoot;
	}
}
