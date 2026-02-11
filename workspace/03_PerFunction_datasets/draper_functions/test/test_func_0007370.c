dump_node(ostream&o, unsigned ind) const
{
      o << setw(ind) << "" << "constant real " << real_
	<< ": " << name();
      if (rise_time())
	    o << " #(" << *rise_time()
	      << "," << *fall_time()
	      << "," << *decay_time() << ")";
      else
	    o << " #(.,.,.)";
      o << endl;
      dump_node_pins(o, ind+4);
}
