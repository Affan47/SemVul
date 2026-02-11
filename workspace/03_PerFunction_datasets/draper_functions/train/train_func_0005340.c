getNewVNI(VNInfo *oldVNI) {
      VNInfo *newVNI = vniMap[oldVNI];

      if (newVNI == 0) {
        newVNI = getNewLI()->createValueCopy(oldVNI,
                                             ls.lis->getVNInfoAllocator());
        vniMap[oldVNI] = newVNI;
      }

      return newVNI;
    }
