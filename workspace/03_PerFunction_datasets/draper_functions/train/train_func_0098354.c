mime_part_add_header (CamelMedium *medium,
                      const gchar *name,
                      gconstpointer value)
{
	CamelMimePart *part = CAMEL_MIME_PART (medium);


	if (mime_part_process_header (medium, name, value))
		camel_header_raw_replace (&part->headers, name, value, -1);
	else
		camel_header_raw_append (&part->headers, name, value, -1);
}
