RemoveFromChain(SQCollectable **chain,SQCollectable *c)
{
	if(c->_prev) c->_prev->_next = c->_next;
	else *chain = c->_next;
	if(c->_next)
		c->_next->_prev = c->_prev;
	c->_next = NULL;
	c->_prev = NULL;
}
