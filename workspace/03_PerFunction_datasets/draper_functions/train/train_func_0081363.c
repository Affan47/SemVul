hpijsfax_get_cb (void *get_cb_data, IjsServerCtx *ctx, IjsJobId job_id,
                  const char *key, char *value_buf, int value_size)
{
	HPIJSFax *pFaxStruct = (HPIJSFax*) get_cb_data;

	if (!strcmp (key, "PrintableArea"))
	{
		return snprintf (value_buf, value_size, "%.4fx%.4f",
		                 pFaxStruct->PrintableWidth (),
						 pFaxStruct->PrintableHeight ());
	}
    else if (!strcmp (key, "DeviceModel"))
    {
        return snprintf (value_buf, value_size, "%s", pFaxStruct->GetDeviceName ());
    }
	else if (!strcmp (key, "PrintableTopLeft"))
	{
		return snprintf (value_buf, value_size, "%.4fx%.4f",
		                 pFaxStruct->PrintableStartX (),
						 pFaxStruct->PrintableStartY ());
	}
	else if (!strcmp (key, "PaperSize"))
	{
		return snprintf (value_buf, value_size, "%.4fx%.4f",
		                 pFaxStruct->PhysicalPageSizeX (),
						 pFaxStruct->PhysicalPageSizeY ());
	}
	else if (!strcmp (key, "Dpi"))
	{
		return snprintf (value_buf, value_size, "%dx%d",
		                 pFaxStruct->EffectiveResolutionX (),
						 pFaxStruct->EffectiveResolutionY ());
	}
	else if (!strcmp (key, "Quality:Quality"))
	{
		return snprintf (value_buf, value_size, "%d", pFaxStruct->GetQuality ());
	}
	else if (!strcmp (key, "Quality:ColorMode"))
	{
		return snprintf (value_buf, value_size, "%d", pFaxStruct->GetColorMode ());
	}
	else if (!strcmp (key, "Quality:MediaType"))
	{
		return snprintf (value_buf, value_size, "%d", pFaxStruct->GetMediaType ());
	}
	else if (!strcmp (key, "FaxEncoding"))
	{
		return snprintf (value_buf, value_size, "%d", pFaxStruct->GetFaxEncoding ());
	}
	else if (!strcmp (key, "ColorSpace"))
	{
	  return snprintf (value_buf, value_size, "%s", pFaxStruct->ph.cs);
	}
	else if (!strcmp (key, "PageImageFormat"))
	{
		return snprintf (value_buf, value_size, "Raster");
	}
	else if (!strcmp (key, "BitsPerSample"))
	{
		return snprintf (value_buf, value_size, "8");
	}


	return IJS_EUNKPARAM;
}
