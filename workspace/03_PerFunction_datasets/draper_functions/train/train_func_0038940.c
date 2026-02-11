__getQualifierCount ( struct native_qualifier * qual,
				      CMPIStatus * rc )
{
	CMPICount c = 0;

	CMSetStatus ( rc, CMPI_RC_OK );

	while ( qual != NULL ) {
		c++;
		qual = qual->next;
	}

	return c;
}
