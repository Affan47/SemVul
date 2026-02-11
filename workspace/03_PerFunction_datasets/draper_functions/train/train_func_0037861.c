has_aa_term(Design*des, NetScope*scope) const
{
      bool flag = false;
      for (unsigned idx = 0 ; idx < parms_.size() ; idx += 1) {
	    flag = parms_[idx]->has_aa_term(des, scope) || flag;
      }
      return flag;
}
