OTF_Reader_readRMAEnd( OTF_RBuffer* buffer,
        OTF_HandlerArray* handlers ) {


        uint32_t ret= 1;

	uint32_t remote;
        uint32_t communicator;
        uint32_t tag;
        uint32_t scltoken;

        if ( handlers->pointer[OTF_RMAEND_RECORD] == NULL ) {

                return OTF_RBuffer_readNewline( buffer );
        }


	remote = OTF_RBuffer_readUint32( buffer );


        ret= ret && ( OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_S_LOCAL_COMMUNICATOR ) ||
                OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_L_LOCAL_COMMUNICATOR ) );
        communicator = OTF_RBuffer_readUint32( buffer );

        ret= ret && ( OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_S_LOCAL_TAG ) ||
                OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_L_LOCAL_TAG ) );
        tag = OTF_RBuffer_readUint32( buffer );

        if( 0 == ret ) {

                PARSE_ERROR( buffer );

                return 0;
        }

        if ( buffer->buffer[buffer->pos] == '\n' ) {

                scltoken = 0;

        } else {


                if ( OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_S_LOCAL_SCL ) ||
                                OTF_RBuffer_testKeyword( buffer, OTF_KEYWORD_L_LOCAL_SCL ) ) {

                        scltoken = OTF_RBuffer_readUint32( buffer );

                } else {

                        PARSE_ERROR( buffer );

                        return 0;
                }
        }

        if ( OTF_RBuffer_readNewline( buffer ) ) {


		return ( OTF_RETURN_OK  == ( (
			(OTF_Handler_RMAEnd*)
			handlers->pointer[OTF_RMAEND_RECORD] )
			( handlers->firsthandlerarg[OTF_RMAEND_RECORD],
			buffer->time, buffer->process, remote, communicator,
			tag, scltoken, buffer->list ) ) );

        } else {

                PARSE_ERROR( buffer );

                return 0;
        }
}
