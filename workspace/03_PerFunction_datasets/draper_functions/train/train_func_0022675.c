setMaximumWidgetSize(int width, int height)
{
   d->m_maxWidth=width;
   d->m_maxHeight=height;

   if (d->m_selectedRegion == d->m_originalPixmap.rect()) d->m_selectedRegion=QRect();
   d->m_originalPixmap=d->m_unzoomedPixmap;


   if ( !d->m_originalPixmap.isNull() &&
       ( d->m_originalPixmap.width() > d->m_maxWidth ||
         d->m_originalPixmap.height() > d->m_maxHeight ) )
   {

         QImage image=d->m_originalPixmap.toImage();
         d->m_originalPixmap=QPixmap::fromImage( image.scaled( width, height, Qt::KeepAspectRatio,Qt::SmoothTransformation ) );
         double oldZoomFactor = d->m_zoomFactor;
         d->m_zoomFactor=d->m_originalPixmap.width()/(double)d->m_unzoomedPixmap.width();

         if (d->m_selectedRegion.isValid())
         {
            d->m_selectedRegion=
                  QRect((int)(d->m_selectedRegion.x()*d->m_zoomFactor/oldZoomFactor),
                        (int)(d->m_selectedRegion.y()*d->m_zoomFactor/oldZoomFactor),
                        (int)(d->m_selectedRegion.width()*d->m_zoomFactor/oldZoomFactor),
                        (int)(d->m_selectedRegion.height()*d->m_zoomFactor/oldZoomFactor) );
         }
   }

   if (!d->m_selectedRegion.isValid()) d->m_selectedRegion = d->m_originalPixmap.rect();

   d->m_linedPixmap=QPixmap();
   d->updatePixmap();
   resize(d->m_label->width(), d->m_label->height());
}
