replaceImageUses(Argument &ImageArg, uint32_t ResourceID,
                        Argument &ImageSizeArg,
                        Argument &ImageFormatArg) {
    bool Modified = false;

    for (auto &Use : ImageArg.uses()) {
      auto Inst = dyn_cast<CallInst>(Use.getUser());
      if (!Inst) {
        continue;
      }

      Function *F = Inst->getCalledFunction();
      if (!F)
        continue;

      Value *Replacement = nullptr;
      StringRef Name = F->getName();
      if (Name.startswith(GetImageResourceIDFunc)) {
        Replacement = ConstantInt::get(Int32Type, ResourceID);
      } else if (Name.startswith(GetImageSizeFunc)) {
        Replacement = &ImageSizeArg;
      } else if (Name.startswith(GetImageFormatFunc)) {
        Replacement = &ImageFormatArg;
      } else {
        continue;
      }

      Inst->replaceAllUsesWith(Replacement);
      InstsToErase.push_back(Inst);
      Modified = true;
    }

    return Modified;
  }
