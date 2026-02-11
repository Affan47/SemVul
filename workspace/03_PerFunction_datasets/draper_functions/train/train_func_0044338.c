getControlFor(FXTable* table){
  register FXComboBox *combo;
  register FXuint justify=0;
  combo=new FXComboBox(table,1,NULL,0,COMBOBOX_STATIC,0,0,0,0,table->getMarginLeft(),table->getMarginRight(),table->getMarginTop(),table->getMarginBottom());
  if(state&LEFT) justify|=JUSTIFY_LEFT;
  if(state&RIGHT) justify|=JUSTIFY_RIGHT;
  if(state&TOP) justify|=JUSTIFY_TOP;
  if(state&BOTTOM) justify|=JUSTIFY_BOTTOM;
  combo->create();
  combo->setJustify(justify);
  combo->setFont(table->getFont());
  combo->setBackColor(table->getBackColor());
  combo->setTextColor(table->getTextColor());
  combo->setSelBackColor(table->getSelBackColor());
  combo->setSelTextColor(table->getSelTextColor());
  combo->fillItems(selections);
  combo->setText(label);
  combo->setNumVisible(FXMIN(20,combo->getNumItems()));
  return combo;
  }
