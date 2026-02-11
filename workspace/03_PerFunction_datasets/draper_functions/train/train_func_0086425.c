initializeAllAnalysisInfo() {
  for (SmallVectorImpl<PMDataManager *>::iterator I = PassManagers.begin(),
         E = PassManagers.end(); I != E; ++I)
    (*I)->initializeAnalysisInfo();


  for (SmallVectorImpl<PMDataManager *>::iterator
       I = IndirectPassManagers.begin(), E = IndirectPassManagers.end();
       I != E; ++I)
    (*I)->initializeAnalysisInfo();

  for (DenseMap<Pass *, Pass *>::iterator DMI = LastUser.begin(),
        DME = LastUser.end(); DMI != DME; ++DMI) {
    SmallPtrSet<Pass *, 8> &L = InversedLastUser[DMI->second];
    L.insert(DMI->first);
  }
}
