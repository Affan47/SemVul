handleVectorStoreIntrinsic(IntrinsicInst &I) {
    IRBuilder<> IRB(&I);
    Value* Addr = I.getArgOperand(0);
    Value *Shadow = getShadow(&I, 1);
    Value *ShadowPtr = getShadowPtr(Addr, Shadow->getType(), IRB);


    IRB.CreateAlignedStore(Shadow, ShadowPtr, 1);

    if (ClCheckAccessAddress)
      insertShadowCheck(Addr, &I);


    if (MS.TrackOrigins)
      IRB.CreateStore(getOrigin(&I, 1), getOriginPtr(Addr, IRB, 1));
    return true;
  }
