neg(IntRelType irt) {
      switch (irt) {
      case IRT_EQ: return IRT_NQ;
      case IRT_NQ: return IRT_EQ;
      case IRT_LQ: return IRT_GR;
      case IRT_LE: return IRT_GQ;
      case IRT_GQ: return IRT_LE;
      case IRT_GR:
      default:
        assert(irt == IRT_GR);
      }
      return IRT_LQ;
    }
