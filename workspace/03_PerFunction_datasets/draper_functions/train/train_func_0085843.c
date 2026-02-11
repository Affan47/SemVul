evolutionVariable() const {
  return
    theBornRandom.second +
    projectionDipole()->invertedTildeKinematics()->evolutionVariable();
}
