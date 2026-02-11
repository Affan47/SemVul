vectorizeBB(BasicBlock &BB) {
      if (skipOptnoneFunction(BB))
        return false;
      if (!DT->isReachableFromEntry(&BB)) {
        DEBUG(dbgs() << "BBV: skipping unreachable " << BB.getName() <<
              " in " << BB.getParent()->getName() << "\n");
        return false;
      }

      DEBUG(if (TTI) dbgs() << "BBV: using target information\n");

      bool changed = false;


      unsigned n = 1;
      for (unsigned v = 2;
           (TTI || v <= Config.VectorBits) &&
           (!Config.MaxIter || n <= Config.MaxIter);
           v *= 2, ++n) {
        DEBUG(dbgs() << "BBV: fusing loop #" << n <<
              " for " << BB.getName() << " in " <<
              BB.getParent()->getName() << "...\n");
        if (vectorizePairs(BB))
          changed = true;
        else
          break;
      }

      if (changed && !Pow2LenOnly) {
        ++n;
        for (; !Config.MaxIter || n <= Config.MaxIter; ++n) {
          DEBUG(dbgs() << "BBV: fusing for non-2^n-length vectors loop #: " <<
                n << " for " << BB.getName() << " in " <<
                BB.getParent()->getName() << "...\n");
          if (!vectorizePairs(BB, true)) break;
        }
      }

      DEBUG(dbgs() << "BBV: done!\n");
      return changed;
    }
