operator<< (ostream&out, const index_component_t&that)
{
      out << "[";
      switch (that.sel) {
	  case index_component_t::SEL_BIT:
	    out << *that.msb;
	    break;
	  case index_component_t::SEL_PART:
	    out << *that.msb << ":" << *that.lsb;
	    break;
	  case index_component_t::SEL_IDX_UP:
	    out << *that.msb << "+:" << *that.lsb;
	    break;
	  case index_component_t::SEL_IDX_DO:
	    out << *that.msb << "-:" << *that.lsb;
	    break;
	  default:
	    out << "???";
	    break;
      }
      out << "]";
      return out;
}
