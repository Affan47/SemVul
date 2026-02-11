insertItem(FXint index,FXHeaderItem* item,FXbool notify){
  register FXint i,d;


  if(!item){ fxerror("%s::insertItem: item is NULL.\n",getClassName()); }


  if(index<0 || items.no()<index){ fxerror("%s::insertItem: index out of range.\n",getClassName()); }


  item->setPos((0<index)?items[index-1]->getPos()+items[index-1]->getSize():0);


  for(i=index,d=item->getSize(); i<items.no(); i++) items[i]->setPos(items[i]->getPos()+d);


  items.insert(index,item);


  if(notify && target){target->tryHandle(this,FXSEL(SEL_INSERTED,message),(void*)(FXival)index);}


  recalc();

  return index;
  }
