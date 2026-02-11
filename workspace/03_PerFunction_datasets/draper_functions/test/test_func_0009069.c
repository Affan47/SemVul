Run() {

  changeset_ty CurrentSet(Roots.begin(), Roots.end());


  changeset_ty Required;


  while (!CurrentSet.empty()) {
    DEBUG({
        llvm::errs() << "DAG_DD - " << CurrentSet.size() << " active changes, "
                     << Required.size() << " required changes\n";
      });


    DeltaActiveSetHelper Helper(*this, Required);
    changeset_ty CurrentMinSet = Helper.Run(CurrentSet);


    Required.insert(CurrentMinSet.begin(), CurrentMinSet.end());


    CurrentSet.clear();
    for (changeset_ty::const_iterator it = CurrentMinSet.begin(),
           ie = CurrentMinSet.end(); it != ie; ++it)
      CurrentSet.insert(pred_begin(*it), pred_end(*it));


  }

  return Required;
}
