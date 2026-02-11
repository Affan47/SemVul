configuration() const
{
    if (const Handler *h = router()->handler(this, "config"))
	if (h->readable())
	    return h->call_read(const_cast<Element *>(this), 0);
    return router()->econfiguration(eindex());
}
