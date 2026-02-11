blogic_alloc_ccb(struct blogic_adapter *adapter)
{
	static unsigned long serial;
	struct blogic_ccb *ccb;
	ccb = adapter->free_ccbs;
	if (ccb != NULL) {
		ccb->serial = ++serial;
		adapter->free_ccbs = ccb->next;
		ccb->next = NULL;
		if (adapter->free_ccbs == NULL)
			blogic_create_addlccbs(adapter, adapter->inc_ccbs,
						true);
		return ccb;
	}
	blogic_create_addlccbs(adapter, adapter->inc_ccbs, true);
	ccb = adapter->free_ccbs;
	if (ccb == NULL)
		return NULL;
	ccb->serial = ++serial;
	adapter->free_ccbs = ccb->next;
	ccb->next = NULL;
	return ccb;
}
