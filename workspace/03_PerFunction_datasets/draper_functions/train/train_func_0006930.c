onChgEntry(FXObject*,FXSelector,void*){
  register FXint value=FXIntVal(textField->getText());
  if(value<range[0]) value=range[0];
  if(value>range[1]) value=range[1];
  if(value!=pos){
    pos=value;
    if(target) target->tryHandle(this,FXSEL(SEL_CHANGED,message),(void*)(FXival)pos);
    }
  return 1;
  }
