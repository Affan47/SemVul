element(const Router *router, int eindex)
{
    if (router && eindex >= 0 && eindex < router->nelements())
	return router->_elements[eindex];
    else if (router && eindex == -1)
	return router->root_element();
    else
	return 0;
}
