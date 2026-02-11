dump() const {
  dbgs() << "PAL[ ";
  for (unsigned i = 0; i < getNumSlots(); ++i) {
    const AttributeWithIndex &PAWI = getSlot(i);
    dbgs() << "{" << PAWI.Index << "," << PAWI.Attrs << "} ";
  }

  dbgs() << "]\n";
}
