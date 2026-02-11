PrintSQ(const SequenceOfItems *sqi, std::ostream & os, std::string const & indent)
{
  if( !sqi ) return;
  SequenceOfItems::ItemVector::const_iterator it = sqi->Items.begin();
  for(; it != sqi->Items.end(); ++it)
    {
    const Item &item = *it;
    const DataSet &ds = item.GetNestedDataSet();
    const DataElement &deitem = item;
    std::string nextindent = indent + "  ";
    os << nextindent << deitem.GetTag();
    os << " ";
    os << "na";
    os << " ";
    if( deitem.GetVL().IsUndefined() )
      {
      os << "(Item with undefined length)";
      }
    else
      {
      os << "(Item with defined length)";
      }
    os << "\n";
    PrintDataSet(ds, os, nextindent + "  ");
    if( deitem.GetVL().IsUndefined() )
      {
      const Tag itemDelItem(0xfffe,0xe00d);
      os << nextindent << itemDelItem << "\n";
      }
    }
  if( sqi->GetLength().IsUndefined() )
    {
    const Tag seqDelItem(0xfffe,0xe0dd);
    os << indent << seqDelItem << "\n";
    }
}
