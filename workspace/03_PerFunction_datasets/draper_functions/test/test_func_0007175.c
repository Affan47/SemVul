attribute(perm_string key) const
{
      for (unsigned idx = 0 ;  idx < nlist_ ;  idx += 1) {

	    if (key == list_[idx].key)
		  return list_[idx].val;
      }

      static const verinum null;
      return null;
}
