getModRefBehavior(ImmutableCallSite CS) {
      ModRefBehavior Min = UnknownModRefBehavior;

      if (const Function* F = CS.getCalledFunction())
        if (FunctionRecord *FR = getFunctionInfo(F)) {
          if (FR->FunctionEffect == 0)
            Min = DoesNotAccessMemory;
          else if ((FR->FunctionEffect & Mod) == 0)
            Min = OnlyReadsMemory;
        }

      return ModRefBehavior(AliasAnalysis::getModRefBehavior(CS) & Min);
    }
