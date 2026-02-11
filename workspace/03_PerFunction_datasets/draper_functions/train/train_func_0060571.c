create(MSDisplayServer *pServer_,const char *pName_)
{
  char buf[255];
  char *bitmap;
  if ((unsigned long)(bitmap=(char *)_pPixmapHashTable->lookup(pName_))==_pPixmapHashTable->notFound())
   {
     MSMessageLog::criticalMessage("MSPixmap error: Unable to create prdefined Pixmap `%s' - unknown name\n",pName_);
     applicationExit();
   }
  else
   {
     int w=PredefinedPixmapWidth;
     int h=PredefinedPixmapHeight;
     sprintf(buf,"Predefined_%s_%d_%d",pName_,1,pServer_->display());
     Pixmap p=XCreateBitmapFromData(pServer_->display(),pServer_->root(),(char *)bitmap,w,h);
     _pData=new MSPixmapData(pServer_,buf,p,p,w,h,1,0,0);
     addToHashTable(buf,(void *)_pData);
     addReference();
   }
}
