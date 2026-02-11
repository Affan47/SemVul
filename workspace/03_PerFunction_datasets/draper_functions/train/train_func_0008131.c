deselectItem(FXint index,FXbool notify){
  if(index<0 || items.no()<=index){ fxerror("%s::deselectItem: index out of range.\n",getClassName()); }
  if(items[index]->isSelected()){
    switch(options&SELECT_MASK){
      case TRACKLIST_EXTENDEDSELECT:
      case TRACKLIST_MULTIPLESELECT:
      case TRACKLIST_SINGLESELECT:
        items[index]->setSelected(false);
        updateItem(index);
        if(notify && target){target->tryHandle(this,FXSEL(SEL_DESELECTED,message),(void*)(FXival)index);}
        break;
      }
    return true;
    }
  return false;
  }
