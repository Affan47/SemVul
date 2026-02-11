drawRectangle(FXDC& dc,FXColor lower,FXColor upper,FXint x,FXint y,FXint w,FXint h){
  register FXint rr,gg,bb,dr,dg,db,r1,g1,b1,r2,g2,b2,yl,yh,yy,dy,n,t;
  const FXint MAXSTEPS=128;

  if(0<w && 0<h){
    dc.setStipple(STIPPLE_NONE);
    dc.setFillStyle(FILL_SOLID);

    r1=FXREDVAL(lower);   r2=FXREDVAL(upper);   dr=r2-r1;
    g1=FXGREENVAL(lower); g2=FXGREENVAL(upper); dg=g2-g1;
    b1=FXBLUEVAL(lower);  b2=FXBLUEVAL(upper);  db=b2-b1;

    n=FXABS(dr);
    if((t=FXABS(dg))>n) n=t;
    if((t=FXABS(db))>n) n=t;
    n++;
    if(n>h) n=h;
    if(n>MAXSTEPS) n=MAXSTEPS;
    rr=(r1<<16)+32767;
    gg=(g1<<16)+32767;
    bb=(b1<<16)+32767;
    yy=32767;

    dr=(dr<<16)/n;
    dg=(dg<<16)/n;
    db=(db<<16)/n;
    dy=(h<<16)/n;

    do {
      yl=yy>>16;
      yy+=dy;
      yh=yy>>16;
      dc.setForeground(FXRGB(rr>>16,gg>>16,bb>>16));
      dc.fillRectangle(x,y+yl,w,yh-yl);
      rr+=dr;
      gg+=dg;
      bb+=db;
    } while(yh<h);
  }
}
