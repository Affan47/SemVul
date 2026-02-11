unapply_vector_scaling_x_NonConst(
    const SmartPtr<const Vector>& v)
  {
    DBG_START_METH("StandardScalingBase::unapply_vector_scaling_x_NonConst",
                   dbg_verbosity);
    SmartPtr<Vector> unscaled_x = v->MakeNewCopy();
    if (IsValid(dx_)) {
      unscaled_x->ElementWiseDivide(*dx_);
    }
    else {
      DBG_PRINT((1, "Creating copy in unapply_vector_scaling_x_NonConst!"));
    }
    return unscaled_x;
  }
