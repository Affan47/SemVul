getHeight(const FXList* list) const {
  register FXFont *font=list->getFont();
  register FXint h=0;
  if(!label.empty()) h=font->getFontHeight();
  return LINE_SPACING+FXMAX(h,SWATCH_HEIGHT);
  }
