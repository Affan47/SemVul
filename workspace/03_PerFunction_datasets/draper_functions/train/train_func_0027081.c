WXMPFiles_SetAbortProc_1 ( XMPFilesRef   xmpObjRef,
                         	    XMP_AbortProc abortProc,
							    void *        abortArg,
							    WXMP_Result * wResult )
{
	XMP_ENTER_ObjWrite ( XMPFiles, "WXMPFiles_SetAbortProc_1" )

		thiz->SetAbortProc ( abortProc, abortArg );

	XMP_EXIT
}
