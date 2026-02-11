publishStart(PublishMode m, const Record &record)
{
	jdns_rr_t *rr = export_record(record);

	int pubmode;
	if(m == QJDns::Unique)
		pubmode = JDNS_PUBLISH_UNIQUE;
	else
		pubmode = JDNS_PUBLISH_SHARED;

	int id = jdns_publish(d->sess, pubmode, rr);
	jdns_rr_delete(rr);
	d->process();
	return id;
}
