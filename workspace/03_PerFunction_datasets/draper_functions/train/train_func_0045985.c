dump() const {
  for (const IndexListEntry *itr = front(); itr != getTail();
       itr = itr->getNext()) {
    dbgs() << itr->getIndex() << " ";

    if (itr->getInstr() != 0) {
      dbgs() << *itr->getInstr();
    } else {
      dbgs() << "\n";
    }
  }

  for (unsigned i = 0, e = MBBRanges.size(); i != e; ++i)
    dbgs() << "BB#" << i << "\t[" << MBBRanges[i].first << ';'
           << MBBRanges[i].second << ")\n";
}
