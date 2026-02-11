hgradient(FXColor left,FXColor right){
  register FXint rr,gg,bb,aa,dr,dg,db,da,r1,g1,b1,a1,r2,g2,b2,a2,x;
  register FXuchar *ptr=(FXuchar*)data;
  register FXuchar *prv=(FXuchar*)data;
  if(ptr && width>1 && height>1){
    r1=FXREDVAL(left);
    r2=FXREDVAL(right);
    rr=(r1<<16)+32768;
    dr=((r2-r1)<<16)/(width-1);
    g1=FXGREENVAL(left);
    g2=FXGREENVAL(right);
    gg=(g1<<16)+32768;
    dg=((g2-g1)<<16)/(width-1);
    b1=FXBLUEVAL(left);
    b2=FXBLUEVAL(right);
    bb=(b1<<16)+32768;
    db=((b2-b1)<<16)/(width-1);
    a1=FXALPHAVAL(left);
    a2=FXALPHAVAL(right);
    aa=(a1<<16)+32768;
    da=((a2-a1)<<16)/(width-1);
    x=width;
    do{
      ptr[0]=rr>>16; rr+=dr;
      ptr[1]=gg>>16; gg+=dg;
      ptr[2]=bb>>16; bb+=db;
      ptr[3]=aa>>16; aa+=da;
      ptr+=4;
      }
    while(--x);
    x=width*(height-1);
    do{
      ptr[0]=prv[0];
      ptr[1]=prv[1];
      ptr[2]=prv[2];
      ptr[3]=prv[3];
      ptr+=4;
      prv+=4;
      }
    while(--x);
    }
  }
