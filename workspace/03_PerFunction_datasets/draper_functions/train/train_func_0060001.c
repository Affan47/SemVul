recompute(){
  FXint ww1,ww2,ww3,hh1,hh2,hh3,hh;


  if(keeppos<0) keeppos=0;
  if(keeppos>length) keeppos=length;


  toppos=rowStart(keeppos);


  hh=font->getFontHeight();


  cursorstart=rowStart(cursorpos);
  cursorend=nextRow(cursorstart);
  cursorcol=indentFromPos(cursorstart,cursorpos);


  if(cursorstart<toprow){
    cursorrow=measureText(0,cursorstart,ww1,hh1);
    toprow=cursorrow+measureText(cursorstart,toppos,ww2,hh2);
    nrows=toprow+measureText(toppos,length+1,ww3,hh3);
    }
  else{
    toprow=measureText(0,toppos,ww1,hh1);
    cursorrow=toprow+measureText(toppos,cursorstart,ww2,hh2);
    nrows=cursorrow+measureText(cursorstart,length+1,ww3,hh3);
    }

  textWidth=FXMAX3(ww1,ww2,ww3);
  textHeight=hh1+hh2+hh3;


  pos_y=-toprow*hh-(-pos_y%hh);


  nvisrows=(height-margintop-marginbottom+hh+hh-1)/hh;
  if(nvisrows<1) nvisrows=1;


  FXRESIZE(&visrows,FXint,nvisrows+1);


  calcVisRows(0,nvisrows);

  FXTRACE((150,"recompute : toprow=%d toppos=%d nrows=%d nvisrows=%d textWidth=%d textHeight=%d length=%d cursorrow=%d cursorcol=%d\n",toprow,toppos,nrows,nvisrows,textWidth,textHeight,length,cursorrow,cursorcol));


  flags&=~FLAG_RECALC;
  }
