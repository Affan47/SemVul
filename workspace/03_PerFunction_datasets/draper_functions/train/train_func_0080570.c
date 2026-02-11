dump(ostream&out, unsigned ind) const
{


      out << setw(ind) << "";
      out << "/* " << get_fileline() << ": " << typeid(*this).name()
	  << " */ ;" << endl;
      dump_attributes_map(out, attributes, ind+2);
}
