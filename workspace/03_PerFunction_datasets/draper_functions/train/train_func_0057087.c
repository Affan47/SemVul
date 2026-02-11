compareGenEvent( GenEvent* e1, GenEvent* e2)
{


   if( e1->event_number() != e2->event_number() ) {
       std::cerr << "compareGenEvent: event numbers differ " << std::endl;
       return false;
   }
   if( e1->signal_process_id() != e2->signal_process_id() ) {
       std::cerr << "compareGenEvent: signal process ids differ " << std::endl;
       return false;
   }
   if( e1->event_scale() != e2->event_scale() ) {
       std::cerr << "compareGenEvent: event scales differ " << std::endl;
       return false;
   }
   if( e1->alphaQCD() != e2->alphaQCD() ) {
       std::cerr << "compareGenEvent: alphaQCD differs " << std::endl;
       return false;
   }
   if( e1->alphaQED() != e2->alphaQED() ) {
       std::cerr << "alphaQED differs " << std::endl;
       return false;
   }
   if( e1->mpi() != e2->mpi() ) {
       std::cerr << "compareGenEvent: mpi differs " << std::endl;
       return false;
   }
   if ( !compareSignalProcessVertex( e1, e2 ) ) { return false; }
   if ( !compareBeamParticles( e1, e2 ) ) { return false; }
   if ( !compareWeights( e1, e2 ) ) { return false; }
   if( e1->random_states() != e2->random_states() ) {
       std::cerr << "compareGenEvent: random states differ " << std::endl;
       return false;
   }
   if( e1->heavy_ion() != e2->heavy_ion() ) {
       std::cerr << "compareGenEvent: heavy ions differ " << std::endl;
       return false;
   }
   if( e1->pdf_info() != e2->pdf_info() ) {
       std::cerr << "compareGenEvent: pdf info differs " << std::endl;
       return false;
   }
   if ( !compareParticles( e1, e2 ) ) { return false; }
   if ( !compareVertices( e1, e2 ) ) { return false; }
   return true;
}
