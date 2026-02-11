colourConnected(tcPPtr first, tcPPtr second) {

  if (!first->coloured() || !second->coloured())
    return false;

  if (first->colourInfo()->colourLine()) {

    if (second->colourInfo()->colourLine() &&
	first->colourInfo()->colourLine() == second->colourInfo()->colourLine())
      return true;

    if (second->colourInfo()->antiColourLine() &&
	first->colourInfo()->colourLine() == second->colourInfo()->antiColourLine())
      return true;

  }

  if (first->colourInfo()->antiColourLine()) {

    if (second->colourInfo()->colourLine() &&
	first->colourInfo()->antiColourLine() == second->colourInfo()->colourLine())
      return true;

    if (second->colourInfo()->antiColourLine() &&
	first->colourInfo()->antiColourLine() == second->colourInfo()->antiColourLine())
      return true;

  }

  return false;

}
