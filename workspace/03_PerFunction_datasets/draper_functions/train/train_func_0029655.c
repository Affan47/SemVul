getXMLIDsForLinkingSubject( PD_DocumentRDFHandle rdf, const std::string& linkingSubj )
{
    std::set< std::string > ret;

    std::stringstream ss;
    ss << "prefix rdf:  <http://www.w3.org/1999/02/22-rdf-syntax-ns#>  " << std::endl
       << "prefix foaf: <http://xmlns.com/foaf/0.1/> " << std::endl
       << "prefix pkg:  <http://docs.oasis-open.org/opendocument/meta/package/common#> " << std::endl
       << "prefix geo84: <http://www.w3.org/2003/01/geo/wgs84_pos#>" << std::endl
       << "" << std::endl
       << "select distinct ?s ?xmlid" << std::endl
       << "where { " << std::endl
       << " ?s pkg:idref ?xmlid " << std::endl
       << " . filter( str(?s) = \"" << linkingSubj << "\" )" << std::endl
       << "}" << std::endl;
    std::set<std::string> uniqfilter;
    PD_RDFQuery q( rdf, rdf );
    UT_DEBUGMSG(("getXMLIDsForLinkingSubject() sparql:%s\n", ss.str().c_str() ));
    PD_ResultBindings_t bindings = q.executeQuery( ss.str() );
    for( PD_ResultBindings_t::iterator iter = bindings.begin(); iter != bindings.end(); ++iter )
    {
        std::map< std::string, std::string > d = *iter;
        std::string xmlid = d["xmlid"];
        if (uniqfilter.count(xmlid))
            continue;
        uniqfilter.insert(xmlid);
        if( !xmlid.empty() )
            ret.insert( xmlid );
    }
    return ret;
}
