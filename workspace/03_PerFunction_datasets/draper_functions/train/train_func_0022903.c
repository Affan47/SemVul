isc_mem_renderxml(xmlTextWriterPtr writer) {
	isc__mem_t *ctx;
	summarystat_t summary;
	isc_uint64_t lost;
	int xmlrc;

	memset(&summary, 0, sizeof(summary));

	TRY0(xmlTextWriterStartElement(writer, ISC_XMLCHAR "contexts"));

	RUNTIME_CHECK(isc_once_do(&once, initialize_action) == ISC_R_SUCCESS);

	LOCK(&lock);
	lost = totallost;
	for (ctx = ISC_LIST_HEAD(contexts);
	     ctx != NULL;
	     ctx = ISC_LIST_NEXT(ctx, link)) {
		xmlrc = renderctx(ctx, &summary, writer);
		if (xmlrc < 0) {
			UNLOCK(&lock);
			goto error;
		}
	}
	UNLOCK(&lock);

	TRY0(xmlTextWriterEndElement(writer));

	TRY0(xmlTextWriterStartElement(writer, ISC_XMLCHAR "summary"));

	TRY0(xmlTextWriterStartElement(writer, ISC_XMLCHAR "TotalUse"));
	TRY0(xmlTextWriterWriteFormatString(writer,
					    "%" ISC_PRINT_QUADFORMAT "u",
					    summary.total));
	TRY0(xmlTextWriterEndElement(writer));

	TRY0(xmlTextWriterStartElement(writer, ISC_XMLCHAR "InUse"));
	TRY0(xmlTextWriterWriteFormatString(writer,
					    "%" ISC_PRINT_QUADFORMAT "u",
					    summary.inuse));
	TRY0(xmlTextWriterEndElement(writer));

	TRY0(xmlTextWriterStartElement(writer, ISC_XMLCHAR "BlockSize"));
	TRY0(xmlTextWriterWriteFormatString(writer,
					    "%" ISC_PRINT_QUADFORMAT "u",
					    summary.blocksize));
	TRY0(xmlTextWriterEndElement(writer));

	TRY0(xmlTextWriterStartElement(writer, ISC_XMLCHAR "ContextSize"));
	TRY0(xmlTextWriterWriteFormatString(writer,
					    "%" ISC_PRINT_QUADFORMAT "u",
					    summary.contextsize));
	TRY0(xmlTextWriterEndElement(writer));

	TRY0(xmlTextWriterStartElement(writer, ISC_XMLCHAR "Lost"));
	TRY0(xmlTextWriterWriteFormatString(writer,
					    "%" ISC_PRINT_QUADFORMAT "u",
					    lost));
	TRY0(xmlTextWriterEndElement(writer));

	TRY0(xmlTextWriterEndElement(writer));
 error:
	return (xmlrc);
}
