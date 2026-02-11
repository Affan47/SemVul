getMDNode(LLVMContext &Context, Value *const *Vals,
                          unsigned NumVals, FunctionLocalness FL,
                          bool Insert) {
  LLVMContextImpl *pImpl = Context.pImpl;


  FoldingSetNodeID ID;
  for (unsigned i = 0; i != NumVals; ++i)
    ID.AddPointer(Vals[i]);

  void *InsertPoint;
  MDNode *N = NULL;

  if ((N = pImpl->MDNodeSet.FindNodeOrInsertPos(ID, InsertPoint)))
    return N;

  bool isFunctionLocal = false;
  switch (FL) {
  case FL_Unknown:
    for (unsigned i = 0; i != NumVals; ++i) {
      Value *V = Vals[i];
      if (!V) continue;
      if (isFunctionLocalValue(V)) {
        isFunctionLocal = true;
        break;
      }
    }
    break;
  case FL_No:
    isFunctionLocal = false;
    break;
  case FL_Yes:
    isFunctionLocal = true;
    break;
  }


  void *Ptr = malloc(sizeof(MDNode)+NumVals*sizeof(MDNodeOperand));
  N = new (Ptr) MDNode(Context, Vals, NumVals, isFunctionLocal);


  pImpl->MDNodeSet.InsertNode(N, InsertPoint);

  return N;
}
