http_layer_data_generator_datastream_body(
          const void* input
        , short* state )
{

    const http_layer_input_t* const http_layer_input
            = ( const http_layer_input_t* ) input;

    ENABLE_GENERATOR();

    BEGIN_CORO( *state )

        {
            memset( buffer_32, 0, 32 );
            sprintf( buffer_32, "%"PRIu32, ( uint32_t ) http_layer_input->xi_context->feed_id );
            gen_ptr_text( *state, buffer_32 );
        }

        gen_ptr_text( *state, XI_CSV_SLASH );
        gen_ptr_text( *state, XI_CSV_DATASTREAMS );
        gen_ptr_text( *state, XI_CSV_SLASH );

        gen_ptr_text( *state, http_layer_input->http_union_data.xi_get_datastream.datastream );
        gen_ptr_text( *state, XI_CSV_DOT_CSV_SPACE );


        gen_ptr_text( *state, XI_HTTP_TEMPLATE_HTTP );
        gen_ptr_text( *state, XI_HTTP_CRLF );


        call_sub_gen_and_exit( *state, input, http_layer_data_generator_query_body );

    END_CORO()

    return 0;
}
