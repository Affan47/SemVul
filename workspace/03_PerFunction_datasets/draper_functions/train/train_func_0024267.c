viewEvent(QEvent* event)
{

   QEvent::Type type = event->type();
   if (type != QEvent::MouseButtonPress &&
       type != QEvent::MouseButtonRelease &&
       type != QEvent::MouseMove) return;


   QMouseEvent* e = dynamic_cast<QMouseEvent *>(event);
   QGraphicsItem* item = findSprite(e->pos());


   switch (event->type())
   {
     case QEvent::MouseButtonPress:
         if (item!=0 && item->type() ==  QGraphicsItem::UserType+100)
           (dynamic_cast<ButtonSprite*>(item))->mousePressEvent(e);
     break;
     case QEvent::MouseButtonRelease:
         if (item!=0 && item->type() ==  QGraphicsItem::UserType+100)
           (dynamic_cast<ButtonSprite*>(item))->mouseReleaseEvent(e);
     break;
     case QEvent::MouseMove:
       if (item != mLastMoveEvent)
       {
         if (mLastMoveEvent!=0 && mLastMoveEvent->type() ==  QGraphicsItem::UserType+100)
         {
           (dynamic_cast<ButtonSprite*>(mLastMoveEvent))->hoverLeaveEvent(e);
         }
         if (item!=0 && item->type() ==  QGraphicsItem::UserType+100)
         {
           (dynamic_cast<ButtonSprite*>(item))->hoverEnterEvent(e);
         }
         mLastMoveEvent = item;
       }
     break;
     default:
     break;
   }
   return;

}
