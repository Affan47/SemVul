ComputeRelatedRegClasses() {


  bool HasAliases = false;
  for (TargetRegisterInfo::regclass_iterator RCI = tri_->regclass_begin(),
       E = tri_->regclass_end(); RCI != E; ++RCI) {
    RelatedRegClasses.insert(*RCI);
    for (TargetRegisterClass::iterator I = (*RCI)->begin(), E = (*RCI)->end();
         I != E; ++I) {
      HasAliases = HasAliases || *tri_->getAliasSet(*I) != 0;

      const TargetRegisterClass *&PRC = OneClassForEachPhysReg[*I];
      if (PRC) {


        RelatedRegClasses.unionSets(PRC, *RCI);
      } else {
        PRC = *RCI;
      }
    }
  }


  if (HasAliases)
    for (DenseMap<unsigned, const TargetRegisterClass*>::iterator
         I = OneClassForEachPhysReg.begin(), E = OneClassForEachPhysReg.end();
         I != E; ++I)
      for (const unsigned *AS = tri_->getAliasSet(I->first); *AS; ++AS) {
        const TargetRegisterClass *AliasClass =
          OneClassForEachPhysReg.lookup(*AS);
        if (AliasClass)
          RelatedRegClasses.unionSets(I->second, AliasClass);
      }
}
