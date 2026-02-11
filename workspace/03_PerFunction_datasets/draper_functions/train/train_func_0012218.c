paintEvent( QPaintEvent *pe )
{
    QPainter p( this );
    p.setClipRegion( pe->region() );
    paintCustomSlider( &p, AmarokConfig::showMoodbarInSlider() );
    p.end();

}
