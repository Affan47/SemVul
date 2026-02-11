vgradient(FXColor top,FXColor bottom){
  register FXint rr,gg,bb,aa,dr,dg,db,da,r1,g1,b1,a1,r2,g2,b2,a2,x,y;
  register FXuchar *ptr=(FXuchar*)data;
  if(ptr && width>1 && height>1){
    r1=FXREDVAL(top);
    r2=FXREDVAL(bottom);
    rr=(r1<<16)+32768;
    dr=((r2-r1)<<16)/(height-1);
    g1=FXGREENVAL(top);
    g2=FXGREENVAL(bottom);
    gg=(g1<<16)+32768;
    dg=((g2-g1)<<16)/(height-1);
    b1=FXBLUEVAL(top);
    b2=FXBLUEVAL(bottom);
    bb=(b1<<16)+32768;
    db=((b2-b1)<<16)/(height-1);
    a1=FXALPHAVAL(top);
    a2=FXALPHAVAL(bottom);
    aa=(a1<<16)+32768;
    da=((a2-a1)<<16)/(height-1);
    y=height;
    do{
      r1=rr>>16; rr+=dr;
      g1=gg>>16; gg+=dg;
      b1=bb>>16; bb+=db;
      a1=aa>>16; aa+=da;
      x=width;
      do{
        ptr[0]=r1;
        ptr[1]=g1;
        ptr[2]=b1;
        ptr[3]=a1;
        ptr+=4;
        }
      while(--x);
      }
    while(--y);
    }
  }
