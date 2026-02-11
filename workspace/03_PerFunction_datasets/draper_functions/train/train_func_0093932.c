xps_find_image_brush_source_part(xps_document *doc, char *base_uri, xml_element *root)
{
	char *image_source_att;
	char buf[1024];
	char partname[1024];
	char *image_name;
	char *profile_name;
	char *p;

	image_source_att = xml_att(root, "ImageSource");
	if (!image_source_att)
		fz_throw(doc->ctx, "cannot find image source attribute");


	if (strstr(image_source_att, "{ColorConvertedBitmap") == image_source_att)
	{
		image_name = NULL;
		profile_name = NULL;

		fz_strlcpy(buf, image_source_att, sizeof buf);
		p = strchr(buf, ' ');
		if (p)
		{
			image_name = p + 1;
			p = strchr(p + 1, ' ');
			if (p)
			{
				*p = 0;
				profile_name = p + 1;
				p = strchr(p + 1, '}');
				if (p)
					*p = 0;
			}
		}
	}
	else
	{
		image_name = image_source_att;
		profile_name = NULL;
	}

	if (!image_name)
		fz_throw(doc->ctx, "cannot find image source");

	xps_resolve_url(partname, base_uri, image_name, sizeof partname);

	return xps_read_part(doc, partname);
}
