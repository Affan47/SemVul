GetTestResult(const changeset_ty &Changes,
                                          const changeset_ty &Required) {
  changeset_ty Extended(Required);
  Extended.insert(Changes.begin(), Changes.end());
  for (changeset_ty::const_iterator it = Changes.begin(),
         ie = Changes.end(); it != ie; ++it)
    Extended.insert(pred_closure_begin(*it), pred_closure_end(*it));

  if (FailedTestsCache.count(Extended))
    return false;

  bool Result = ExecuteOneTest(Extended);
  if (!Result)
    FailedTestsCache.insert(Extended);

  return Result;
}
