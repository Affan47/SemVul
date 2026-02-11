getPageLocs(PlasmaVer pv, bool all) const {
    std::vector<plLocation> locs;

    for (size_t i=0; i < fPages.getSize(); i++) {
        if (all || !(fPages[i].fLoadFlags & kDontLoadMask))
            locs.push_back(getPageLoc(i, pv));
    }

    return locs;
}
