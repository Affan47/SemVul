internalBondsPresent(TEditedMolecule * mQuery, TSimpleMolecule * mStructure) {
    std::vector<int> aList(mStructure->nAtoms());
    std::vector<int> bList(mStructure->nBonds());
    unsigned int i, n1, n2;
    bool result=false;

    for (i=0; i<aList.size(); i++) aList[i]=0;
    for (i=0; i<bList.size(); i++) bList[i]=0;
    for (i=0; i<mQuery->nAtoms(); i++) aList[mQuery->queryAQTested[i]]=1;
    for (i=0; i<mQuery->nBonds(); i++) bList[mQuery->queryBQTested[i]]=1;
    for (i=0; i<bList.size(); i++) if (bList[i] == 0) {
        n1=mStructure->getBond(i)->at[0];
        n2=mStructure->getBond(i)->at[1];
        if ((aList[n1] == 1) && (aList[n2] == 1)) result=true;
        if (result) break;
      };

    return result;
  }
