selectInRectangle(FXint x,FXint y,FXint w,FXint h,FXbool notify){
  register FXint index;
  register FXbool changed=false;
  for(index=0; index<items.no(); index++){
    if(hitItem(index,x,y,w,h)){
      changed|=selectItem(index,notify);
      }
    }
  return changed;
  }
