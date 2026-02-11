generateDiagram(OBMol * pmol) {
    TEditedMolecule sm;
    OBAtom * atom;

    sm.readOBMol(pmol);

    TemplateRedraw tr;
    tr.redrawFine(sm);
    for (unsigned int i=1; i<=pmol->NumAtoms(); i++) {
      atom=pmol->GetAtom(i);
      atom->SetVector(sm.getAtom(i-1)->rx,-sm.getAtom(i-1)->ry,0.0);
    };
  }
