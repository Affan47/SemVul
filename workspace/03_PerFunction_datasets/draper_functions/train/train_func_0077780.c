csv_layer_parse_datastream(
        csv_layer_data_t* csv_layer_data
      , const_data_descriptor_t* data
      , const layer_hint_t hint
      , xi_datapoint_t* dp )
{
    XI_UNUSED( hint );
    XI_UNUSED( dp );


    signed char ret_state = 0;
    static struct xi_tm gmtinfo;


    const const_data_descriptor_t pattern1   = { XI_CSV_TIMESTAMP_PATTERN, strlen( XI_CSV_TIMESTAMP_PATTERN ), strlen( XI_CSV_TIMESTAMP_PATTERN ), 0 };
    void* pv1[]                              = {
        ( void* ) &( gmtinfo.tm_year )
        , ( void* ) &( gmtinfo.tm_mon )
        , ( void* ) &( gmtinfo.tm_mday )
        , ( void* ) &( gmtinfo.tm_hour )
        , ( void* ) &( gmtinfo.tm_min )
        , ( void* ) &( gmtinfo.tm_sec )
        , ( void* ) &( dp->timestamp.micro ) };

    const const_data_descriptor_t pattern2   = { ",", 1, 1, 0 };


    BEGIN_CORO( csv_layer_data->datapoint_decode_state )

    memset( &gmtinfo, 0, sizeof( struct xi_tm ) );


    {


        do
        {

            ret_state = xi_stated_sscanf( &( csv_layer_data->stated_sscanf_state ), &pattern1, data, pv1 );

            if( ret_state == 0 )
            {

                YIELD( csv_layer_data->datapoint_decode_state, LAYER_STATE_WANT_READ );
                ret_state = 0;
                continue;
            }

        } while( ret_state == 0 );


        do
        {
            ret_state = xi_stated_sscanf( &( csv_layer_data->stated_sscanf_state ), &pattern2, data, 0 );

            if( ret_state == 0 )
            {

                YIELD( csv_layer_data->datapoint_decode_state, LAYER_STATE_WANT_READ );
                ret_state = 0;
                continue;
            }

        } while( ret_state == 0 );


        if( ret_state == -1 )
        {
            EXIT( csv_layer_data->datapoint_decode_state, LAYER_STATE_ERROR );
        }


        gmtinfo.tm_year            -= 1900;
        gmtinfo.tm_mon             -= 1;
        dp->timestamp.timestamp     = xi_mktime( &gmtinfo );
    }


    {
        do
        {
            ret_state = xi_stated_csv_decode_value( &( csv_layer_data->csv_decode_value_state ), data, dp, hint );

            if( ret_state == 0 )
            {
                YIELD( csv_layer_data->datapoint_decode_state, LAYER_STATE_WANT_READ )
                continue;
            }

        } while( ret_state == 0 );
    }


    EXIT( csv_layer_data->datapoint_decode_state, ( ret_state == -1 ? LAYER_STATE_ERROR : LAYER_STATE_OK ) );

    END_CORO()


}
