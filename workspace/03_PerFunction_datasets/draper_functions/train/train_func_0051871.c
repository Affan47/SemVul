getDepthFactor(Value *V) {


      if (isa<InsertElementInst>(V) || isa<ExtractElementInst>(V))
        return 0;


      if (!Config.NoMemOpBoost && (isa<LoadInst>(V) || isa<StoreInst>(V)))
        return Config.ReqChainDepth/2;

      return 1;
    }
