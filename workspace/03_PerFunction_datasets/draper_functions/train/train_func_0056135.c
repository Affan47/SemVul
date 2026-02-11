getReplacementPointerInput(LLVMContext& Context,
                     Instruction *I, Instruction *J, unsigned o) {
    Value *IPtr, *JPtr;
    unsigned IAlignment, JAlignment, IAddressSpace, JAddressSpace;
    int64_t OffsetInElmts;


    (void) getPairPtrInfo(I, J, IPtr, JPtr, IAlignment, JAlignment,
                          IAddressSpace, JAddressSpace,
                          OffsetInElmts, false);


    Value *VPtr = IPtr;

    Type *ArgTypeI = IPtr->getType()->getPointerElementType();
    Type *ArgTypeJ = JPtr->getType()->getPointerElementType();
    Type *VArgType = getVecTypeForPair(ArgTypeI, ArgTypeJ);
    Type *VArgPtrType
      = PointerType::get(VArgType,
                         IPtr->getType()->getPointerAddressSpace());
    return new BitCastInst(VPtr, VArgPtrType, getReplacementName(I, true, o),
                         I);
  }
