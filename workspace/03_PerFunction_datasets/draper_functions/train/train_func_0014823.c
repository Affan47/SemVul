remove(Function *F) {


  ComparableFunction CF = ComparableFunction(F, ComparableFunction::LookupOnly);
  if (FnSet.erase(CF)) {
    DEBUG(dbgs() << "Removed " << F->getName() << " from set and deferred it.\n");
    Deferred.push_back(F);
  }
}
