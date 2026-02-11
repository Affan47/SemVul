qitem_alloc(int nbytes) {
    qitem *it;
    unsigned int id;
    int ndatasize;
	ndatasize = sizeof(qitem) + nbytes;

    id = slabs_clsid(ndatasize);
    if (id == 0)
        return 0;

    it = slabs_alloc(ndatasize);
    if (it == 0)
		return 0;

	it->next = 0;
    it->nbytes = nbytes;
	it->store_time = time(0);

    return it;
}
