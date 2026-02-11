DimensionsSet() const
  {
    Index total_dim= 0;
    bool valid = true;
    for (Index i=0; i<ncomp_spaces_; i++) {
      if (block_dim_[i] == -1) {
        valid = false;
        break;
      }
      total_dim += block_dim_[i];
    }

    if (valid) {
      DBG_ASSERT(total_dim == Dim());
    }

    return valid;
  }

}
