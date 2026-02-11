doinit() {
  GeneralHardME::doinit();
  fermion_.resize(numberOfDiags());
  vector_.resize(numberOfDiags());
  flowME().resize(numberOfFlows(),
		  ProductionMatrixElement(PDT::Spin1Half, PDT::Spin1,
					  PDT::Spin1, PDT::Spin1Half));
  diagramME().resize(numberOfDiags(),
		     ProductionMatrixElement(PDT::Spin1Half, PDT::Spin1,
					     PDT::Spin1, PDT::Spin1Half));
  for(HPCount ix = 0; ix < numberOfDiags(); ++ix) {
    HPDiagram diagram = getProcessInfo()[ix];
    PDT::Spin offspin = diagram.intermediate->iSpin();
    if(diagram.channelType == HPDiagram::sChannel ||
       ( diagram.channelType == HPDiagram::tChannel
	 && offspin == PDT::Spin1Half)) {
      AbstractFFVVertexPtr vert1 = dynamic_ptr_cast<AbstractFFVVertexPtr>
		(diagram.vertices.first);
      AbstractFFVVertexPtr vert2 = dynamic_ptr_cast<AbstractFFVVertexPtr>
	(diagram.vertices.second);
      fermion_[ix] = make_pair(vert1, vert2);
    }
    else {
      if(offspin == PDT::Spin1) {
	AbstractFFVVertexPtr vert1 = dynamic_ptr_cast<AbstractFFVVertexPtr>
	  (diagram.vertices.first);
	AbstractVVVVertexPtr vert2 = dynamic_ptr_cast<AbstractVVVVertexPtr>
	  (diagram.vertices.second);
	vector_[ix] = make_pair(vert1, vert2);
      }
    }
  }
}
