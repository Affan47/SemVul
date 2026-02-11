setBid(const XMLCh *bid1)
{
	if(bid)XMLString::release(&bid);
	bid=XMLString::replicate(bid1);
}
