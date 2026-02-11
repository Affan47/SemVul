dump_node(ostream&o, unsigned ind) const
{
      o << setw(ind) << "";

      switch (edge_) {
	  case ANYEDGE:
	    o << "anyedge ";
	    break;
	  case POSEDGE:
	    o << "posedge ";
	    break;
	  case NEGEDGE:
	    o << "negedge ";
	    break;
      }
      o << setw(ind) << "" << "-> " << scope_path(event_->scope()) << "." << event_->name() << "; " << endl;
      dump_node_pins(o, ind+4);
      dump_obj_attr(o, ind+4);
}
