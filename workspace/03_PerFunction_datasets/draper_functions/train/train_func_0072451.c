Colors (ostream& out) {
  if (!svg_format()) {
    FgColor(out);
    BgColor(out);
  } else {

    PSColor* fgcolor = (PSColor*) GetOverlayComp()->GetGraphic()->GetFgColor();
    PSColor* bgcolor = (PSColor*) GetOverlayComp()->GetGraphic()->GetBgColor();

    ColorIntensity fr, fg, fb;
    fgcolor->GetIntensities(fr, fg, fb);

    out << "stroke: rgb("
	<< (int)(fr*100) << "%,"
	<< (int)(fg*100) << "%,"
	<< (int)(fb*100) << "%); ";

    ColorIntensity br, bg, bb;
    bgcolor->GetIntensities(br, bg, bb);

    PSPattern* pat = (PSPattern*) GetOverlayComp()->GetGraphic()->GetPattern();
    if (pat != nil && !pat->None() &&
	pat->GetGrayLevel()>=0.0 && pat->GetGrayLevel()<=1.0) {

      float fp = 100.0*(1.0-pat->GetGrayLevel());
      float bp = 100.0-fp;
      out << "fill: rgb("
	  << (int)(fr*fp+br*bp) << "%,"
	  << (int)(fg*fp+bg*bp) << "%,"
	  << (int)(fb*fp+bb*bp) << "%); ";
    }
  }

}
