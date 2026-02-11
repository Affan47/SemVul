SwapData( void* const data, const int size, const int wcount )

{
    uint8* data8 = reinterpret_cast<uint8*>(data);
    std::size_t count = wcount;

    if( size == 2 )
    {
        uint8 t;

        for( ; count; count-- )
        {
            t = data8[0];
            data8[0] = data8[1];
            data8[1] = t;

            data8 += 2;
        }
    }
    else if( size == 1 )
        ;
    else if( size == 4 )
    {
        uint8 t;

        for( ; count; count-- )
        {
            t = data8[0];
            data8[0] = data8[3];
            data8[3] = t;

            t = data8[1];
            data8[1] = data8[2];
            data8[2] = t;

            data8 += 4;
        }
    }
    else if( size == 8 )
    {
        uint8 t;

        for( ; count; count-- )
        {
            t = data8[0];
            data8[0] = data8[7];
            data8[7] = t;

            t = data8[1];
            data8[1] = data8[6];
            data8[6] = t;

            t = data8[2];
            data8[2] = data8[5];
            data8[5] = t;

            t = data8[3];
            data8[3] = data8[4];
            data8[4] = t;

            data8 += 8;
        }
    }
    else
        ThrowPCIDSKException( "Unsupported data size in SwapData()" );
}
