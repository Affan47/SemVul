dump_events_(ostream&out, unsigned indent) const
{
      for (map<perm_string,PEvent*>::const_iterator cur = events.begin()
		 ; cur != events.end() ;  cur ++ ) {
	    PEvent*ev = (*cur).second;
	    out << setw(indent) << "" << "event " << ev->name() << "; // "
		<< ev->get_fileline() << endl;
      }
}
