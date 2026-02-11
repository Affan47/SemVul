isSafeAllocaToScalarRepl(AllocaInst *AI) {


  AllocaInfo Info(AI);

  isSafeForScalarRepl(AI, 0, Info);
  if (Info.isUnsafe) {
    DEBUG(dbgs() << "Cannot transform: " << *AI << '\n');
    return false;
  }


  if (Info.isMemCpySrc && Info.isMemCpyDst &&
      HasPadding(AI->getAllocatedType(), *TD))
    return false;


  if (!Info.hasSubelementAccess && Info.hasALoadOrStore) {

    if (StructType *ST = dyn_cast<StructType>(AI->getAllocatedType())) {
      if (ST->getNumElements() > 1) return false;
    } else {
      if (cast<ArrayType>(AI->getAllocatedType())->getNumElements() > 1)
        return false;
    }
  }

  return true;
}
