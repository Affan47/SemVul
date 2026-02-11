test_platform()
    {

    Twofish_Byte buf[] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0};
    Twofish_UInt32 C;
    Twofish_UInt32 x,y;
    int i;


    if( ((Twofish_UInt32)((Twofish_UInt32)1 << 31) == 0) || ((Twofish_UInt32)-1 < 0 ))
        {
	  Twofish_fatal( "Twofish code: Twofish_UInt32 type not suitable", ERR_UINT32 );
        }
    if( (sizeof( Twofish_Byte ) != 1) || (((Twofish_Byte)-1) < 0) )
        {
	  Twofish_fatal( "Twofish code: Twofish_Byte type not suitable", ERR_BYTE );
        }


    if( (GET32( buf ) != 0x78563412UL) || (GET32(buf+1) != 0x9a785634UL)
        || (GET32( buf+2 ) != 0xbc9a7856UL) || (GET32(buf+3) != 0xdebc9a78UL) )
        {
	  Twofish_fatal( "Twofish code: GET32 not implemented properly", ERR_GET32 );
        }


    C = GET32( buf );
    PUT32( 3*C, buf );
    if( GET32( buf ) != 0x69029c36UL )
        {
	  Twofish_fatal( "Twofish code: PUT32 not implemented properly", ERR_PUT32 );
        }


    for( i=1; i<32; i++ )
        {

        x = ROR32( C, i );
        y = ROL32( C, i );
        x ^= (C>>i) ^ (C<<(32-i));

        y ^= (C<<i) ^ (C>>(32-i));
        x |= y;


	if( (x & 0xffffffffUL) != 0 )
            {
	      Twofish_fatal( "Twofish ROL or ROR not properly defined.", ERR_ROLR );
            }
        }


    if( BSWAP(C) != 0x12345678UL )
        {


	  Twofish_fatal( "BSWAP not properly defined.", ERR_BSWAP );
        }


    if( (b0(C)!=0x12) || (b1(C) != 0x34) || (b2(C) != 0x56) || (b3(C) != 0x78) )
        {


	  Twofish_fatal( "Twofish code: SELECT_BYTE not implemented properly", ERR_SELECTB );
        }
    return SUCCESS;
    }
