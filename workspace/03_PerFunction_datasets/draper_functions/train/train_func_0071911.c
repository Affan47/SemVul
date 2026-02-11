setFont(FXFont *fnt,FXbool notify){
  if(!fnt){ fxerror("%s::setFont: NULL font specified.\n",getClassName()); }
  if(font!=fnt){
    font=fnt;
    recalc();
    update();
    if(notify && target) target->tryHandle(this,FXSEL(SEL_CHANGED,message),NULL);
    }
  }
