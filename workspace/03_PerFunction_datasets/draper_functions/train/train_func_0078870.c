dump_node(ostream&o, unsigned ind) const
{
      o << setw(ind) << "" << "logic: ";
      switch (type_) {
	  case AND:
	    o << "and";
	    break;
	  case BUF:
	    o << "buf";
	    break;
	  case BUFIF0:
	    o << "bufif0";
	    break;
	  case BUFIF1:
	    o << "bufif1";
	    break;
	  case CMOS:
	    o << "cmos";
	    break;
	  case NAND:
	    o << "nand";
	    break;
	  case NMOS:
	    o << "nmos";
	    break;
	  case NOR:
	    o << "nor";
	    break;
	  case NOT:
	    o << "not";
	    break;
	  case NOTIF0:
	    o << "notif0";
	    break;
	  case NOTIF1:
	    o << "notif1";
	    break;
	  case OR:
	    o << "or";
	    break;
	  case PULLDOWN:
	    o << "pulldown";
	    break;
	  case PULLUP:
	    o << "pullup";
	    break;
	  case RCMOS:
	    o << "rcmos";
	    break;
	  case RNMOS:
	    o << "rnmos";
	    break;
	  case RPMOS:
	    o << "rpmos";
	    break;
	  case PMOS:
	    o << "pmos";
	    break;
	  case XNOR:
	    o << "xnor";
	    break;
	  case XOR:
	    o << "xor";
	    break;
      }
      o << " #(" << rise_time()
	<< "," << fall_time() << "," << decay_time() << ") " << name()
	<< " scope=" << scope_path(scope())
	<< endl;

      dump_node_pins(o, ind+4);
      dump_obj_attr(o, ind+4);
}
