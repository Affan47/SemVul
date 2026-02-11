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

  for (MBB2IdxMap::const_iterator itr = mbb2IdxMap.begin();
       itr != mbb2IdxMap.end(); ++itr) {
    dbgs() << "MBB " << itr->first->getNumber() << " (" << itr->first << ") - ["
           << itr->second.first << ", " << itr->second.second << "]\n";
  }
}
