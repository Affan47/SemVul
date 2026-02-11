LLVMConstIntOfArbitraryPrecision(LLVMTypeRef IntTy,
                                              unsigned NumWords,
                                              const uint64_t Words[]) {
    IntegerType *Ty = unwrap<IntegerType>(IntTy);
    return wrap(ConstantInt::get(Ty->getContext(),
                                 APInt(Ty->getBitWidth(),
                                       makeArrayRef(Words, NumWords))));
}
