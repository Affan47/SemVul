makeItemVisible(FXint index){
  register FXint x,y,hh,px,py;
  if(0<=index && index<items.no()){


    viewable=index;


    if(xid){


      if(flags&FLAG_RECALC) layout();

      px=pos_x;
      py=pos_y;


      if(options&(ICONLIST_BIG_ICONS|ICONLIST_MINI_ICONS)){
        if(options&ICONLIST_COLUMNS){
          FXASSERT(ncols>0);
          x=itemSpace*(index%ncols);
          y=itemHeight*(index/ncols);
          }
        else{
          FXASSERT(nrows>0);
          x=itemSpace*(index/nrows);
          y=itemHeight*(index%nrows);
          }
        if(px+x+itemSpace >= viewport_w) px=viewport_w-x-itemSpace;
        if(px+x <= 0) px=-x;
        if(py+y+itemHeight >= viewport_h) py=viewport_h-y-itemHeight;
        if(py+y <= 0) py=-y;
        }


      else{
        hh=header->getDefaultHeight();
        y=hh+index*itemHeight;
        if(py+y+itemHeight >= viewport_h+hh) py=hh+viewport_h-y-itemHeight;
        if(py+y <= hh) py=hh-y;
        }


      setPosition(px,py);


      viewable=-1;
      }
    }
  }
