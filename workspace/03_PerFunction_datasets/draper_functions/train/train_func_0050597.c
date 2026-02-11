initialise_mds_tables()
    {
    int i;
    Twofish_UInt32 q,qef,q5b;


    for( i=0; i<256; i++ )
        {


        q = q_table[0][i];


        qef = (q >> 1) ^ mds_poly_divx_const[ q & 1 ];


        q5b = (qef >> 1) ^ mds_poly_divx_const[ qef & 1 ] ^ q;


        qef ^= q5b;


        MDS_table[1][i] = (q  <<24) | (q5b<<16) | (qef<<8) | qef;
        MDS_table[3][i] = (q5b<<24) | (qef<<16) | (q  <<8) | q5b;


        q = q_table[1][i];
        qef = (q >> 1) ^ mds_poly_divx_const[ q & 1 ];
        q5b = (qef >> 1) ^ mds_poly_divx_const[ qef & 1 ] ^ q;
        qef ^= q5b;


        MDS_table[0][i] = (qef<<24) | (qef<<16) | (q5b<<8) | q  ;
        MDS_table[2][i] = (qef<<24) | (q  <<16) | (qef<<8) | q5b;
        }
    }
