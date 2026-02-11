write_xml (void * context, Writer & writer)
{
	UT_Error err = UT_OK;

	static const char * psz_id = "id";
	static const char * psz_content_type = "type";
	static const char * psz_description = "desc";

	const char * atts[8];

	atts[4] = NULL;
	atts[5] = NULL;

	for (UT_uint32 i = 0; i < m_resource_count; i++)
		if (m_resource[i]->bInternal)
			{
				XAP_InternalResource * ri = dynamic_cast<XAP_InternalResource *>(m_resource[i]);

				UT_uint32 n = 0;

				atts[n++] = psz_id;
				atts[n++] = ri->name().utf8_str ();

				if (!(ri->type().empty ()))
					{
						atts[n++] = psz_content_type;
						atts[n++] = ri->type().utf8_str ();
					}
				if (!(ri->Description.empty ()))
					{
						atts[n++] = psz_description;
						atts[n++] = ri->Description.utf8_str ();
					}
				atts[n++] = NULL;
				atts[n++] = NULL;

				err = writer.write_xml (context, "resource", atts);
				if (err != UT_OK) break;

				err = ri->write_base64 (context, writer);
				if (err != UT_OK) break;

				err = writer.write_xml (context, "resource");
				if (err != UT_OK) break;
			}
	return err;
}
