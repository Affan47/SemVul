setScaleTicks( int minLen, int medLen,
                             int majLen, int penWidth )
{
    QwtDialScaleDraw *sd = d_data->scaleDraw;
    if ( sd )
    {
        sd->setTickLength( QwtScaleDiv::MinorTick, minLen );
        sd->setTickLength( QwtScaleDiv::MediumTick, medLen );
        sd->setTickLength( QwtScaleDiv::MajorTick, majLen );
        sd->setPenWidth( penWidth );
    }
}
