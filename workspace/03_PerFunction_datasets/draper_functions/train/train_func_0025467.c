test( CoderInfo::MatchType isReadable_,
          CoderInfo::MatchType isWritable_,
          CoderInfo::MatchType isMultiFrame_ )
{
  int result = 0;
  list<CoderInfo> coderList;
  coderInfoList( &coderList, isReadable_, isWritable_, isMultiFrame_ );
  list<CoderInfo>::iterator entry = coderList.begin();
  while( entry != coderList.end() )
    {

      if ( isReadable_ != CoderInfo::AnyMatch &&
           (( entry->isReadable() && isReadable_ != CoderInfo::TrueMatch ) ||
            ( !entry->isReadable() && isReadable_ != CoderInfo::FalseMatch )) )
        {
          cout << "Entry \""
               << entry->name()
               << "\" has unexpected readablity state ("
               << static_cast<int>(entry->isReadable())
               << ")"
               << endl;
          ++result;
        }


      if ( isWritable_ != CoderInfo::AnyMatch &&
           (( entry->isWritable() && isWritable_ != CoderInfo::TrueMatch ) ||
            ( !entry->isWritable() && isWritable_ != CoderInfo::FalseMatch )) )
        {
          cout << "Entry \""
               << entry->name()
               << "\" has unexpected writablity state ("
               << static_cast<int>(entry->isWritable())
               << ")"
               << endl;
          ++result;
        }


      if ( isMultiFrame_ != CoderInfo::AnyMatch &&
           (( entry->isMultiFrame() && isMultiFrame_ != CoderInfo::TrueMatch ) ||
            ( !entry->isMultiFrame() && isMultiFrame_ != CoderInfo::FalseMatch )) )
        {
          cout << "Entry \""
               << entry->name()
               << "\" has unexpected multiframe state ("
               << static_cast<int>(entry->isMultiFrame())
               << ")"
               << endl;
          ++result;
        }

      entry++;
    }

  return result;
}
