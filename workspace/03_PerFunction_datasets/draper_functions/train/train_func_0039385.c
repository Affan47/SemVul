ExportTIFF_LocTextASCII ( const SXMPMeta & xmp, const char * xmpNS, const char * xmpProp,
						  TIFF_Manager * tiff, XMP_Uns8 ifd, XMP_Uns16 id )
{
	try {

		std::string xmpValue;

		bool foundXMP = xmp.GetLocalizedText ( xmpNS, xmpProp, "", "x-default", 0, &xmpValue, 0 );
		if ( ! foundXMP ) {
			tiff->DeleteTag ( ifd, id );
			return;
		}

		tiff->SetTag ( ifd, id, kTIFF_ASCIIType, (XMP_Uns32)( xmpValue.size()+1 ), xmpValue.c_str() );

	} catch ( ... ) {


	}

}
