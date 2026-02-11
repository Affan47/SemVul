killSelection(FXbool notify){
  FXTablePos tablepos;
  FXTableItem *item;
  if(isAnythingSelected()){
    for(tablepos.row=selection.fm.row; tablepos.row<=selection.to.row; tablepos.row++){
      for(tablepos.col=selection.fm.col; tablepos.col<=selection.to.col; tablepos.col++){
        item=cells[tablepos.row*ncols+tablepos.col];
        if(item){ item->setSelected(FALSE); }
        updateItem(tablepos.row,tablepos.col);
        if(notify && target) target->tryHandle(this,FXSEL(SEL_DESELECTED,message),(void*)&tablepos);
        }
      }
    selection.fm.row=-1;
    selection.fm.col=-1;
    selection.to.row=-1;
    selection.to.col=-1;
    return TRUE;
    }
  return FALSE;
  }
