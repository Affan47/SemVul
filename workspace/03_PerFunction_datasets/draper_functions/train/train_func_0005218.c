hoverLeft()
{
    d->hoverTimer.stop();
    d->hoverTimer.setDirection( QTimeLine::Backward );
    d->hoveredOver = false;
    if( d->hoverTimer.currentFrame() != 0 )
        d->hoverTimer.start();
}
