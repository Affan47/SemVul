WXMPUtils_MergeFromJPEG_1 ( XMPMetaRef    wfullXMP,
                            XMPMetaRef    wextendedXMP,
                            WXMP_Result * wResult )
{
	XMP_ENTER_Static ( "WXMPUtils_MergeFromJPEG_1" )

		if ( wfullXMP == 0 ) XMP_Throw ( "Output XMP pointer is null", kXMPErr_BadParam );
		if ( wfullXMP == wextendedXMP ) XMP_Throw ( "Full and extended XMP pointers match", kXMPErr_BadParam );

		XMPMeta * fullXMP = WtoXMPMeta_Ptr ( wfullXMP );
		XMP_AutoLock fullXMPLock ( &fullXMP->lock, kXMP_WriteLock );

		const XMPMeta & extendedXMP = WtoXMPMeta_Ref ( wextendedXMP );
		XMP_AutoLock extendedXMPLock ( &extendedXMP.lock, kXMP_ReadLock );

		XMPUtils::MergeFromJPEG ( fullXMP, extendedXMP );

	XMP_EXIT
}
