GetBlockDC(const PicArray& pic_data,
                                            int xunit , int yunit , int split, CompSort cs)
{
    BlockDiffParams dparams;

    if ( cs!=Y_COMP )
        dparams.SetBlockLimits( m_predparams->ChromaBParams( split ) ,
                                pic_data, xunit , yunit);
    else
        dparams.SetBlockLimits( m_predparams->LumaBParams( split ) ,
                                pic_data, xunit , yunit);

    IntraBlockDiff intradiff( pic_data );

    return intradiff.CalcDC( dparams );
}
