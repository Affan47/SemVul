drawText(FXint x,FXint y,const FXchar* string,FXuint len){


  FXfloat xx,yy;
  tfm(xx,yy,(FXfloat)x,(FXfloat)y);


  FXfloat fsize=0.1f*font->getSize();


  FXString fname=font->getName();
  if(fname=="times"){
    fname="Times";
    }
  else if(fname=="helvetica"){
    fname="Helvetica";
    }
  else if(fname=="courier"){
    fname="Courier";
    }
  else{
    fname="Courier";
    }
  if(font->getWeight()==FXFont::Bold){
    if(font->getSlant()==FXFont::Italic){
      fname+="-BoldItalic";
      }
    else if(font->getSlant()==FXFont::Oblique){
      fname+="-BoldOblique";
      }
    else {
      fname+="-Bold";
      }
    }
  else{
    if(font->getSlant()==FXFont::Italic){
      fname+="-Italic";
      }
    else if(font->getSlant()==FXFont::Oblique){
      fname+="-Oblique";
      }
    }
  if(fname=="Times"){
    fname+="-Roman";
    }

  outf("(%s) %g %g %d /%s drawText\n",string,xx,yy,(int)fsize,fname.text());
  }
