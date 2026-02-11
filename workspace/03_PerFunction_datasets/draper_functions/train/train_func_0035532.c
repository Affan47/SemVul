getDefaultWidth(){
  register FXint w=0;
  if(!caption.empty()) w=font->getTextWidth(caption.text(),caption.length());
  return padleft+padright+(border<<1)+w;
  }
