colourGeometries(tcDiagPtr diag) const {

  static const ColourLines cqqbar("1 3 5,-2 -3 -5");

  static const ColourLines cqg("1 2 -3, 3 -2 5");

  static const ColourLines cqbarg("-1 -2 3, -3 2 -5");

  static const ColourLines cgg[6]={ColourLines("1 2 5, -3 -5, 3 -2 -1"),
			     ColourLines("-1 -2 -5, 3 5, -3 2 1"),
			     ColourLines("1 5, -1 -2 3, -3 2 -5"),
			     ColourLines("-1 -5, 1 2 -3, 3 -2 5"),
			     ColourLines("1 3 5, -5 -3 -2, 2 -1"),
			     ColourLines("-1 -3 -5, 5 3 2 ,-2 1")};

  Selector<const ColourLines *> sel;
  if ( diag->id() == -1)      sel.insert(1.0, &cqqbar);
  else if ( diag->id() == -2) sel.insert(1.0, &cqg);
  else if ( diag->id() == -3) sel.insert(1.0, &cqbarg);
  else
    {
      sel.insert(0.5, &cgg[2*(abs(diag->id())-4)  ]);
      sel.insert(0.5, &cgg[2*(abs(diag->id())-4)+1]);
    }

  return sel;
}
