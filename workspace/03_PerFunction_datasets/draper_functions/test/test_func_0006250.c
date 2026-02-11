publishUpdate(JDnsSharedRequest *obj, const QJDns::Record &record)
{
	if(!requests.contains(obj))
		return;

	obj->d->ppmode = determinePpMode(record);
	obj->d->pubrecord = manipulateRecord(record, obj->d->ppmode);


	foreach(Handle h, obj->d->handles)
		h.jdns->publishUpdate(h.id, obj->d->pubrecord);
}
