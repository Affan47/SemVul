contentsDragMoveEvent( QDragMoveEvent *e )
{
   if( ! acceptDrag( e ) )
   {
      e->ignore();
      return;
   }
   e->acceptProposedAction();


   Q3ListViewItem *afterme;
   Q3ListViewItem *parent;

   findDrop( e->pos(), parent, afterme );


   Q3ListViewItem *item = afterme ? afterme : parent;

   if( item && item->isSelectable() )
   {
      setSelected( item, true );
      if( item != m_dropItem ) {
         m_autoOpenTimer->stop();
         m_dropItem = item;
         m_autoOpenTimer->start( (QApplication::startDragTime() * 3) / 2 );
      }
   }
   else
   {
      m_autoOpenTimer->stop();
      m_dropItem = 0;
   }
}
