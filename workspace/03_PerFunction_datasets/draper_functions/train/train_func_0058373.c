saveQTableToFile( const TQuantizationTable &qTable, const string &filename )
{
    FILE *f = mrpt::system::os::fopen( filename, "wt" );

    typedef map<int,map<int,map<int,deque<pair<TFeatureID, double> > > > > TQuantizationTable;

    TQuantizationTable::const_iterator                                    it1;
    map<int,map<int,deque<pair<TFeatureID, double> > > >::const_iterator  it2;
    map<int,deque<pair<TFeatureID, double> > >::const_iterator            it3;

    for( it1 = qTable.begin(); it1 != qTable.end(); ++it1 )
        for( it2 = it1->second.begin(); it2 != it1->second.end(); ++it2 )
            for( it3 = it2->second.begin(); it3 != it2->second.end(); ++it3 )
            {
                mrpt::system::os::fprintf( f, "%d\t%d\t%d\t", it1->first, it2->first, it3->first );
                for( int k = 0; k < int(it3->second.size()); ++k )
                    mrpt::system::os::fprintf( f, "%lu\t%.2f\t",static_cast<long unsigned int>(it3->second[k].first), it3->second[k].second );
                mrpt::system::os::fprintf( f, "\n" );
            }
    mrpt::system::os::fclose( f );
}
