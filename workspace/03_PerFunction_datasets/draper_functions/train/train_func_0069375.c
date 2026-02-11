DotImpl(const Vector &x) const
  {
    DBG_START_METH("CompoundVector::DotImpl", dbg_verbosity);
    DBG_ASSERT(vectors_valid_);
    const CompoundVector* comp_x = static_cast<const CompoundVector*>(&x);
    DBG_ASSERT(dynamic_cast<const CompoundVector*>(&x));
    DBG_ASSERT(NComps() == comp_x->NComps());
    Number dot = 0.;
    for (Index i=0; i<NComps(); i++) {
      DBG_ASSERT(ConstComp(i));
      dot += ConstComp(i)->Dot(*comp_x->GetComp(i));
    }
    return dot;
  }
