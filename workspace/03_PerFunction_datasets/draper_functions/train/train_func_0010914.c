ConsistencyCheck()

{
    Synchronize();

    std::string report = CPCIDSKSegment::ConsistencyCheck();

    report += ConsistencyCheck_Header();
    report += ConsistencyCheck_DataIndices();
    report += ConsistencyCheck_ShapeIndices();

    if( report != "" )
        fprintf( stderr, "ConsistencyCheck() Report:\n%s", report.c_str() );

    return report;
}
