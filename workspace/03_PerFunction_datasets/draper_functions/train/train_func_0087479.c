setCurrent(FXint panel,FXbool notify){
  register FXint nc=isMemberOf(&FXTabBook::metaClass)?numChildren()>>1:numChildren();
  if(panel!=current && 0<=panel && panel<nc){
    current=panel;
    recalc();
    if(notify && target){ target->tryHandle(this,FXSEL(SEL_COMMAND,message),(void*)(FXival)current); }
    }
  }
