doGetChildTestAt( int index ) const
{
  if ( hasOnlyOneTest() )
    return getUniqueChildTest()->getChildTestAt( index );
  return TestSuite::doGetChildTestAt( index );
}
