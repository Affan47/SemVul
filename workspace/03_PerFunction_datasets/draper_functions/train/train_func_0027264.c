WXMPFiles_CTor_1 ( WXMP_Result * wResult )
{
	XMP_ENTER_Static ( "WXMPFiles_CTor_1" )

		XMPFiles * newObj = new XMPFiles();
		++newObj->clientRefs;
		XMP_Assert ( newObj->clientRefs == 1 );
		wResult->ptrResult = newObj;

	XMP_EXIT
}
