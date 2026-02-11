extractText(FXString& text,FXint startrow,FXint endrow,FXint startcol,FXint endcol,const FXchar* cs,const FXchar* rs) const {
  register FXint ncs,nrs,sz,r,c,p;
  FXString string;


  if(cs==NULL || rs==NULL){ fxerror("%s::extractText: bad argument.\n",getClassName()); }


  if(startrow<0 || startcol<0 || nrows<=endrow || ncols<=endcol){ fxerror("%s::extractText: index out of range.\n",getClassName()); }


  text.clear();


  if(startrow<=endrow && startcol<=endcol){

    ncs=strlen(cs);
    nrs=strlen(rs);


    sz=(endrow-startrow)*((endcol-startcol)*ncs+nrs);


    for(r=startrow; r<=endrow; r++){
      for(c=startcol; c<=endcol; c++){
        sz+=getItemText(r,c).length();
        }
      }


    text.length(sz);
    for(r=startrow,p=0; r<=endrow; r++){
      for(c=startcol; c<=endcol; c++){
        string=getItemText(r,c);
        text.replace(p,string.length(),string);
        p+=string.length();
        if(c==endcol){
          text.replace(p,nrs,rs,nrs);
          p+=nrs;
          }
        else{
          text.replace(p,ncs,cs,ncs);
          p+=ncs;
          }
        }
      }
    }
  }
