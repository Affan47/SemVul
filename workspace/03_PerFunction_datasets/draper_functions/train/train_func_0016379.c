emit_fcodehdr(const char *starter_name)
{


    if ( fcode_written )
    {
        tokenization_error( TKERROR ,
	    "Cannot create FCode header after FCode output has begun.\n");
        if ( ! noerrors ) return ;
    }

	fcode_header_t *fcode_hdr;

	fcode_start_ob_off = opc;
	emit_token( starter_name );

	fcode_hdr_ob_off = opc;
	fcode_hdr = (fcode_header_t *)(ostart+fcode_hdr_ob_off);

	EMIT_STRUCT(fcode_header_t);

	fcode_body_ob_off = opc;


	fcode_hdr->format = 0x08;

}
