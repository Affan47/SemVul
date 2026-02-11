updateDipole(list<Dipole>::iterator dip) {

  dip->update();

  if (hasLeftNeighbour(dip)) {

    list<Dipole>::iterator theLeftNeighbour =
      leftNeighbourIterator(dip);

    theLeftNeighbour->rightParticle(dip->leftParticle());
    theLeftNeighbour->rightPDF(dip->leftPDF());
    theLeftNeighbour->rightFraction(dip->leftFraction());

    theLeftNeighbour->update();

  }

  if (hasRightNeighbour(dip)) {

    list<Dipole>::iterator theRightNeighbour =
      rightNeighbourIterator(dip);

    theRightNeighbour->leftParticle(dip->rightParticle());
    theRightNeighbour->leftPDF(dip->rightPDF());
    theRightNeighbour->leftFraction(dip->rightFraction());

    theRightNeighbour->update();

  }

}
