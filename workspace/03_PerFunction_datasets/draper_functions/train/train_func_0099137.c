show()
{
    if( !d->sharedRenderer )
    {

        return;
    }
    if( d->widget && d->widget->rect() != d->widgetRect )
    {
        d->widgetRect = d->widget->rect();
        d->scene->setSceneRect( d->widget->rect() );
        d->view->setFixedSize( d->widget->size() );
        update();
    }

    d->fadeShowTimer.stop();
    if( ( d->fade == PopupDropper::FadeIn || d->fade == PopupDropper::FadeInOut ) && d->fadeInTime > 0 )
    {

        d->fadeShowTimer.setDuration( d->fadeInTime );
        d->fadeShowTimer.setCurrentTime( 0 );
        d->fadeShowTimer.setCurveShape( QTimeLine::EaseOutCurve );
        QColor color = d->windowColor;
        color.setAlpha( 0 );
        setPalette( color );
        foreach( PopupDropperItem* pdi, d->pdiItems )
            pdi->setSubitemOpacity( 0.0 );
        d->fadeShowTimer.start();

    }
    d->view->show();
}
