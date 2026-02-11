operator<<( std::ostream &out, GRA_legend const &legend )
{
  GRA_setOfCharacteristics *legendC = legend.graphWindow_->GetGraphLegendCharacteristics();
  std::size_t size = legend.entries_.size();
  out << "<graphlegend size=\"" << size
      << "\" frameon=\""
      << (static_cast<GRA_boolCharacteristic*>(legendC->Get(wxT("FRAMEON")))->Get()?1L:0L)
      << "\" titleon=\""
      << (static_cast<GRA_boolCharacteristic*>(legendC->Get(wxT("TITLEON")))->Get()?1L:0L)
      << "\" xlo=\"" << legend.xlo_ << "\" ylo=\"" << legend.ylo_
      << "\" xhi=\"" << legend.xhi_ << "\" yhi=\"" << legend.yhi_
      << "\">\n";
  for( std::size_t i=0; i<size; ++i )out << *legend.entries_[i];
  out << *legend.frame_ << *legend.title_;
  return out << "</graphlegend>\n";
}
