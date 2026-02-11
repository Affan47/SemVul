dump(ostream&out, unsigned ind) const
{
      out << setw(ind) << "" << "forever /* " << get_fileline() << " */" << endl;
      statement_->dump(out, ind+3);
}
