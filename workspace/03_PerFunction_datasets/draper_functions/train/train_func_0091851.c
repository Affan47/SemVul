onMotion(FXObject*,FXSelector,void* ptr){
  register FXEvent *event=(FXEvent*)ptr;
  register FXint xx,yy,ww,hh,lo,hi,h,travel;
  register FXdouble p;
  if(!isEnabled()) return 0;
  if(flags&FLAG_PRESSED){
    yy=border+padtop+2;
    xx=border+padleft+2;
    hh=height-(border<<1)-padtop-padbottom-4;
    ww=width-(border<<1)-padleft-padright-4;
    if(options&REALSLIDER_VERTICAL){
      h=event->win_y-dragpoint;
      travel=hh-headsize;
      if(h<yy) h=yy;
      if(h>yy+travel) h=yy+travel;
      if(h!=headpos){
        FXMINMAX(lo,hi,headpos,h);
        headpos=h;
        update(border,lo-1,width-(border<<1),hi+headsize+2-lo);
        }
      if(travel>0)
        p=range[0]+((range[1]-range[0])*(yy+travel-h))/travel;
      else
        p=range[0];
      }
    else{
      h=event->win_x-dragpoint;
      travel=ww-headsize;
      if(h<xx) h=xx;
      if(h>xx+travel) h=xx+travel;
      if(h!=headpos){
        FXMINMAX(lo,hi,headpos,h);
        headpos=h;
        update(lo-1,border,hi+headsize+2-lo,height-(border<<1));
        }
      if(travel>0)
        p=range[0]+((range[1]-range[0])*(h-xx))/travel;
      else
        p=range[0];
      }
    if(p<range[0]) p=range[0];
    if(p>range[1]) p=range[1];
    if(pos!=p){
      pos=p;
      flags|=FLAG_CHANGED;
      if(target) target->tryHandle(this,FXSEL(SEL_CHANGED,message),(void*)&pos);
      }
    return 1;
    }
  return 0;
  }
