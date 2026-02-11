generateDiagram(OBMol * pmol, std::ostream & ofs) {
  TEditedMolecule sm;
  OBAtom * atom;

  sm.readOBMol(pmol);
  sm.refofs=&ofs;

  TemplateRedraw tr;
  tr.redrawFine(sm);
  restoreDoubleBonds(sm,false);
  for (int i=1; i<=pmol->NumAtoms(); i++) {
    atom=pmol->GetAtom(i);
    atom->SetVector(sm.getAtom(i-1)->rx,sm.getAtom(i-1)->ry,0.0);

  };
  sm.getMolfile(ofs);
}
