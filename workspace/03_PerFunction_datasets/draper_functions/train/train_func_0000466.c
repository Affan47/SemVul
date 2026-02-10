addWidget(QGraphicsItem *widget)
{
   if (!widget) {
       return;
   }

   if (widget == d->mChildItem)
       return;

   if (d->mChildItem != 0) {
       d->mChildItem->setParentItem(0);
       delete d->mChildItem;
   }

   if (widget) {
       widget->setParentItem(this);
       d->mChildItem = widget;
   }
}
