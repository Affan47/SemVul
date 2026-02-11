printLastEvent(ostream& os) const {

  os << "--- PowhegInclusiveME last event information -----------------------------------\n";

  os << " '" << name() << "' for Born/virtual\n '"
     << head()->name() << "'\n";

  os << " Born/virtual event information:\n";
  dynamic_ptr_cast<Ptr<MatchboxNLOME>::tptr>(head())->printLastEvent(os);

  os << " dipoles event information:\n";
  for ( MEVector::const_iterator d = dependent().begin();
	d != dependent().end(); ++d ) {
    dynamic_ptr_cast<Ptr<SubtractionDipole>::tptr>(*d)->printLastEvent(os);
    dynamic_ptr_cast<Ptr<SubtractionDipole>::tptr>(*d)->reweights().front()->printLastEvent(os);
  }


  os << "--- end PowhegInclusiveME last event information -------------------------------\n\n\n";

  os << flush;

}
