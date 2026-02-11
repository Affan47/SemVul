Decoding_of_the_coded_Log_Area_Ratios (LARc,LARpp)
word    * LARc;
word    * LARpp;
{
        register word   temp1 ;
        register long   ltmp;


#undef  STEP
#define STEP( B, MIC, INVA )    \
                temp1    = GSM_ADD( *LARc++, MIC ) << 10;       \
                temp1    = GSM_SUB( temp1, B << 1 );            \
                temp1    = GSM_MULT_R( INVA, temp1 );           \
                *LARpp++ = GSM_ADD( temp1, temp1 );

        STEP(      0,  -32,  13107 );
        STEP(      0,  -32,  13107 );
        STEP(   2048,  -16,  13107 );
        STEP(  -2560,  -16,  13107 );

        STEP(     94,   -8,  19223 );
        STEP(  -1792,   -8,  17476 );
        STEP(   -341,   -4,  31454 );
        STEP(  -1144,   -4,  29708 );


}
