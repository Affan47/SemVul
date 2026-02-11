layout(){


  FXScrollArea::layout();


  if(firstitem){
    vertical->setLine(firstitem->getHeight(this));
    horizontal->setLine(firstitem->getWidth(this)/10);
    }


  update();


  if(viewableitem){
    makeItemVisible(viewableitem);
    }


  flags&=~FLAG_DIRTY;
  }
