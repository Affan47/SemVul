layout(){
#if FOXVERSION < FXVERSION(1,7,0)

  FXScrollArea::layout();


  header->position(0,0,viewport_w,header->getDefaultHeight());
  header->show();


  vertical->setLine(lineHeight);
  horizontal->setLine(header->getTotalSize());


  if(0<=viewable){
    makeItemVisible(viewable);
    }


  update();

  flags&=~FLAG_DIRTY;
#else
  FXint hh=header->getDefaultHeight();


  placeScrollBars(width,height-hh);


  header->position(0,0,width,hh);


  vertical->setLine(lineHeight);
  horizontal->setLine(header->getTotalSize());


  if(0<=viewable){
    makeItemVisible(viewable);
    }


  update();


  flags&=~FLAG_DIRTY;
#endif

  }
