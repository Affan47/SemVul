camel_mime_message_set_date (CamelMimeMessage *message,
                             time_t date,
                             gint offset)
{
	gchar *datestr;

	g_assert (message);

	if (date == CAMEL_MESSAGE_DATE_CURRENT) {
		struct tm local;
		gint tz;

		date = time (NULL);
		camel_localtime_with_offset (date, &local, &tz);
		offset = (((tz / 60 / 60) * 100) + (tz / 60 % 60));
	}
	message->date = date;
	message->date_offset = offset;

	datestr = camel_header_format_date (date, offset);
	CAMEL_MEDIUM_CLASS (camel_mime_message_parent_class)->set_header ((CamelMedium *) message, "Date", datestr);
	g_free (datestr);
}
