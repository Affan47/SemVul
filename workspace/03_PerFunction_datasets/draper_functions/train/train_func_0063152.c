doinit() {
  GeneralThreeBodyDecayer::doinit();
  unsigned int ndiags = getProcessInfo().size();
  _sca.resize(ndiags);
  _fer.resize(ndiags);
  _vec.resize(ndiags);
  _ten.resize(ndiags);
  for(unsigned int ix = 0;ix < ndiags; ++ix) {
    TBDiagram current = getProcessInfo()[ix];
    tcPDPtr offshell = current.intermediate;
    if( offshell->CC() ) offshell = offshell->CC();
    if(offshell->iSpin() == PDT::Spin0) {
      AbstractSSSVertexPtr vert1 = dynamic_ptr_cast<AbstractSSSVertexPtr>
	(current.vertices.first);
      AbstractFFSVertexPtr vert2 = dynamic_ptr_cast<AbstractFFSVertexPtr>
	(current.vertices.second);
      if(!vert1||!vert2) throw Exception()
	<< "Invalid vertices for a scalar diagram in StoSFFDecayer::doinit()"
	<< Exception::runerror;
      _sca[ix] = make_pair(vert1, vert2);
    }
    else if(offshell->iSpin() == PDT::Spin1Half) {
      AbstractFFSVertexPtr vert1 = dynamic_ptr_cast<AbstractFFSVertexPtr>
	(current.vertices.first);
      AbstractFFSVertexPtr vert2 = dynamic_ptr_cast<AbstractFFSVertexPtr>
	(current.vertices.second);
      if(!vert1||!vert2) throw Exception()
	<< "Invalid vertices for a fermion diagram in StoSFFDecayer::doinit()"
	<< Exception::runerror;
      _fer[ix] = make_pair(vert1, vert2);
    }
    else if(offshell->iSpin() == PDT::Spin1) {
      AbstractVSSVertexPtr vert1 = dynamic_ptr_cast<AbstractVSSVertexPtr>
	(current.vertices.first);
      AbstractFFVVertexPtr vert2 = dynamic_ptr_cast<AbstractFFVVertexPtr>
	(current.vertices.second);
      if(!vert1||!vert2) throw Exception()
	<< "Invalid vertices for a vector diagram in StoSFFDecayer::doinit()"
	<< Exception::runerror;
      _vec[ix] = make_pair(vert1, vert2);
    }
    else if(offshell->iSpin() == PDT::Spin2) {
      AbstractSSTVertexPtr vert1 = dynamic_ptr_cast<AbstractSSTVertexPtr>
	(current.vertices.first);
      AbstractFFTVertexPtr vert2 = dynamic_ptr_cast<AbstractFFTVertexPtr>
	(current.vertices.second);
      if(!vert1||!vert2) throw Exception()
	<< "Invalid vertices for a tensor diagram in StoSFFDecayer::doinit()"
	<< Exception::runerror;
      _ten[ix] = make_pair(vert1, vert2);
    }
  }
}
