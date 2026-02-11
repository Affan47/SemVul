streamTo(SourceStream &s) const
{
  s << SourceStream::Endl << "continue";
  if (!ident.isNull())
    s << ' ' << ident;
  s << ';';
}
