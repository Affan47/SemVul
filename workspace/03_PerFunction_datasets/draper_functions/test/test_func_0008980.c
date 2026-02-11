mime_message_write_to_stream_sync (CamelDataWrapper *data_wrapper,
                                   CamelStream *stream,
                                   GCancellable *cancellable,
                                   GError **error)
{
	CamelDataWrapperClass *data_wrapper_class;
	CamelMimeMessage *mm = CAMEL_MIME_MESSAGE (data_wrapper);


	if (mm->from == NULL) {

		g_warning ("No from set for message");
		camel_medium_set_header ((CamelMedium *) mm, "From", "");
	}
	if (!camel_medium_get_header ((CamelMedium *) mm, "Date"))
		camel_mime_message_set_date (mm, CAMEL_MESSAGE_DATE_CURRENT, 0);

	if (mm->subject == NULL)
		camel_mime_message_set_subject (mm, "No Subject");

	if (mm->message_id == NULL)
		camel_mime_message_set_message_id (mm, NULL);


	if (!camel_medium_get_header ((CamelMedium *) mm, "Mime-Version"))
		camel_medium_set_header ((CamelMedium *) mm, "Mime-Version", "1.0");


	data_wrapper_class = CAMEL_DATA_WRAPPER_CLASS (
		camel_mime_message_parent_class);
	return data_wrapper_class->write_to_stream_sync (
		data_wrapper, stream, cancellable, error);
}
