itemIcon( K3FileTreeViewItem *item, int gap ) const
{
   QPixmap pix;
   kDebug(250) << "Setting icon for column " << gap;

   if( item )
   {

      KFileTreeBranch *brnch = item->branch();
      if( item == brnch->root() )
      {
	 pix = brnch->pixmap();
	 if( m_wantOpenFolderPixmaps && brnch->root()->isOpen() )
	 {
	    pix = brnch->openPixmap();
	 }
      }
      else
      {

         pix = item->fileItem().pixmap( KIconLoader::SizeSmall );


         if( item->isDir() && m_wantOpenFolderPixmaps )
         {
            if( isOpen( static_cast<Q3ListViewItem*>(item)))
               pix = m_openFolderPixmap;
         }
      }
   }

   return pix;
}
