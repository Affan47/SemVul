doinitrun(){
  CascadeHandler::doinitrun();

  if(MPIHandler_){
    MPIHandler_->initialize();
    if(MPIHandler_->softInt())
      remDec_->initSoftInteractions(MPIHandler_->Ptmin(), MPIHandler_->beta());
  }


}
