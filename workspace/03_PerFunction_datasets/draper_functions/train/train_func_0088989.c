getDeclaration(Module *M, ID id, ArrayRef<Type*> Tys) {


  return
    cast<Function>(M->getOrInsertFunction(getName(id, Tys),
                                          getType(M->getContext(), id, Tys)));
}
