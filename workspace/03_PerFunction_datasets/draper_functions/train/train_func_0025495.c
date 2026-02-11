moveSegments(FXint sglo,FXint sghi,FXdouble val,FXbool notify){
  register FXdouble delta, below,above,room;
  register FXint i;
  if(0<=sglo && sghi<nsegs && sglo<=sghi){
    below=seg[sglo].middle-seg[sglo].lower;
    above=seg[sghi].upper-seg[sglo].middle;
    room=seg[sghi].middle-seg[sglo].middle;
    if(sglo==0){
      if(val<seg[0].lower) val=seg[0].lower;
      }
    else{
      if(val-below<seg[sglo-1].middle) val=seg[sglo-1].middle+below;
      }
    if(sghi==nsegs-1){
      if(val+room>seg[nsegs-1].upper) val=seg[nsegs-1].upper-room;
      }
    else{
      if(val+above>seg[sghi+1].middle) val=seg[sghi+1].middle-above;
      }
    delta=val-seg[sglo].middle;
    if(delta!=0.0){
      for(i=sglo; i<=sghi; i++){
        if(0<i) seg[i].lower+=delta;
        seg[i].middle+=delta;
        if(i<nsegs-1) seg[i].upper+=delta;
        }
      if(0<sglo){
        seg[sglo-1].upper=seg[sglo].lower;
        }
      if(sghi<nsegs-1){
        seg[sghi+1].lower=seg[sghi].upper;
        }
      recalc();
      if(notify && target){target->tryHandle(this,FXSEL(SEL_CHANGED,message),(void*)(FXival)-1);}
      }
    }
  }
