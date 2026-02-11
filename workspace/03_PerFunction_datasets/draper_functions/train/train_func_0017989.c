dvb_table_sdt_free(struct dvb_table_sdt *sdt)
{
	struct dvb_table_sdt_service *service = sdt->service;
	while(service) {
		dvb_free_descriptors((struct dvb_desc **) &service->descriptor);
		struct dvb_table_sdt_service *tmp = service;
		service = service->next;
		free(tmp);
	}
	free(sdt);
}
