persistentOutput(PersistentOStream & os) const {
  os << theSearchPath << theNormalOrderedLegs
     << theIndexMap << theFlowMap;
  writeBasis();
}
