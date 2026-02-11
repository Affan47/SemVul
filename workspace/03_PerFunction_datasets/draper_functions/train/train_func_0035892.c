HPDF_Image_LoadRaw1BitImageFromMem  (HPDF_Doc           pdf,
                           const HPDF_BYTE   *buf,
                          HPDF_UINT          width,
                          HPDF_UINT          height,
						  HPDF_UINT          line_width,
						  HPDF_BOOL          black_is1,
						  HPDF_BOOL			 top_is_first)
{
    HPDF_Image image;

    HPDF_PTRACE ((" HPDF_Image_Load1BitImageFromMem\n"));

    if (!HPDF_HasDoc (pdf))
        return NULL;

    image = HPDF_Image_Load1BitImageFromMem(pdf->mmgr, buf, pdf->xref, width,
                height, line_width, top_is_first);

    if (!image)
        HPDF_CheckError (&pdf->error);

    if (pdf->compression_mode & HPDF_COMP_IMAGE)
	{
		image->filter = HPDF_STREAM_FILTER_CCITT_DECODE;
		image->filterParams = HPDF_Dict_New(pdf->mmgr);
		if(image->filterParams==NULL) {
			return NULL;
		}


		HPDF_Dict_AddNumber (image->filterParams, "K", -1);

		HPDF_Dict_AddNumber (image->filterParams, "Columns", width);

		HPDF_Dict_AddNumber (image->filterParams, "Rows", height);
		HPDF_Dict_AddBoolean (image->filterParams, "BlackIs1", black_is1);
	}

    return image;
}
