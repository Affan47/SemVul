tr_iwant_matrix_extended()
{
  assert(is_device());
  assert(!subckt());
  assert(ext_nodes() + int_nodes() == matrix_nodes());

  for (int ii = 0;  ii < matrix_nodes();  ++ii) {
    if (_n[ii].m_() >= 0) {
      for (int jj = 0;  jj < ii ;  ++jj) {
	_sim->_aa.iwant(_n[ii].m_(),_n[jj].m_());
	_sim->_lu.iwant(_n[ii].m_(),_n[jj].m_());
      }
    }else{itested();

    }
  }
}
