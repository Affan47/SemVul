operator<(const RetOrArg &O) const {
        if (F != O.F)
          return F < O.F;
        else if (Idx != O.Idx)
          return Idx < O.Idx;
        else
          return IsArg < O.IsArg;
      }
