DatAusgeben(int n) {
  print_to_stderr(_sprintf("%3d.: %d,%d,%d\n",
			   n, gAufnahme[n].mArt,
			   gAufnahme[n].mD1, gAufnahme[n].mD2));
}
