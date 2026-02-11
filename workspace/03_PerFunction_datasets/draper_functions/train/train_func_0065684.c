streamTo(SourceStream &s) const
{
    s << UString::from(value());
}
