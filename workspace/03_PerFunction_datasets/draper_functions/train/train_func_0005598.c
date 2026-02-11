setupFont(){
  FXString fontname = font->getActualName() +", " + FXStringVal(font->getSize()/10);
  if(font->getWeight()!=0 && font->getWeight()!=FXFont::Normal){
    fontname += ", " + weightToString(font->getWeight());
    }
  if (font->getSlant()!=0 && font->getSlant()!=FXFont::Straight){
    fontname += ", " + slantToString(font->getSlant());
    }

  tabitem->setFont(font);
  label1->setFont(font);
  label2->setFont(font);
  label3->setFont(font);
  label4->setFont(font);
  label5->setFont(font);

  menulabels[0]->setFont(font);
  menulabels[1]->setFont(font);
  menulabels[2]->setFont(font);
  menulabels[3]->setFont(font);
  menulabels[4]->setFont(font);
  menulabels[5]->setFont(font);

  textfield1->setFont(font);
  fontbutton->setText(fontname);
  }
