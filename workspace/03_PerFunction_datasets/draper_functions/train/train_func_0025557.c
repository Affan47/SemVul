DbgDump(std::ostream* out) const
{
  TableType::const_iterator i;
  for(i = m_Table.begin(); i != m_Table.end(); ++i) {
    *out << " key: '" << i->first << "' score: ";
    *out << "(num scores: " << (i->second).size() << ")";
    for(size_t j = 0; j < (i->second).size(); ++j) {
      *out << (i->second)[j] << " ";
    }
    *out << "\n";
  }
}
