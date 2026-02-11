create(MSDisplayServer *pServer_,const char *pName_,const char *bitmap_,
		      int w_,int h_,unsigned long fg_,unsigned long bg_)
{
  int dep=DefaultDepthOfScreen(pServer_->screen());
  Pixmap p=XCreatePixmapFromBitmapData(pServer_->display(),pServer_->root(),(char*)bitmap_,
				       w_,h_,fg_,bg_,dep);
  _pData=new MSPixmapData(pServer_,pName_,p,w_,h_,dep,fg_,bg_);
  addToHashTable(pName_,(void *)_pData);
  addReference();
}
