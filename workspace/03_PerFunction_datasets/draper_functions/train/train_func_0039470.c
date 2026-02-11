pointHover (QwtPlotCurve *curve, int index)
{
    if ( index >= 0 && curve != intervalHighlighterCurve )
    {
        double x_value = curve->sample( index ).x();
        double y_value = curve->sample( index ).y();


        QString text = QString( "%1 %2 %3 %4 %5" )
              . arg( this->axisTitle( curve->xAxis() ).text() )
              . arg( x_value, 0, 'f', 3 )
              . arg( "\n" )
              . arg( this->axisTitle( curve->yAxis() ).text() )
              . arg( y_value, 0, 'f', 3 );


        tooltip->setText( text );
    }
    else
    {

        tooltip->setText( "" );
    }
}
