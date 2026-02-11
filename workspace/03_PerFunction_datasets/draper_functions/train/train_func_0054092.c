update()
{
    UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() TOP\n" ));
    UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() our   version:%ld\n", getVersion() ));
    UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() their version:%ld\n", m_delegate->getVersion() ));

    if( getVersion() >= m_delegate->getVersion() )
    {
        UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() nothing to be done...\n" ));
        return;
    }

    PP_AttrProp* AP = new PP_AttrProp();
    UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() 1\n" ));
    UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() sparql:%s\n", getSparql().c_str() ));

    PD_RDFQuery q( m_rdf, m_delegate );
    PD_ResultBindings_t bindings = q.executeQuery( getSparql() );
    UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() 2\n" ));

    for( PD_ResultBindings_t::iterator iter = bindings.begin(); iter != bindings.end(); ++iter )
    {
        std::map< std::string, std::string > d = *iter;

        PD_URI    s( d["s"] );
        PD_URI    p( d["p"] );

        int objectType = PD_Object::OBJECT_TYPE_URI;
        PD_Object dobj = m_delegate->getObject( s, p );
        UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() dobj.valid:%d dobj.type:%d dobj.str:%s \n",
                     dobj.isValid(),
                     dobj.getObjectType(),
                     dobj.toString().c_str() ));
        if( dobj.isValid() )
            objectType = dobj.getObjectType();

        PD_Object o( d["o"], objectType );


        POCol l;
        const gchar* szName = s.toString().c_str();
        const gchar* szValue = 0;
        if( AP->getProperty( szName, szValue) )
        {
            l = decodePOCol(szValue);
        }
        l.insert( std::make_pair( p, o ));
        std::string po = encodePOCol(l);
        AP->setProperty( szName, po.c_str() );

        PD_RDFStatement st( s, p, o );
        UT_DEBUGMSG(("RDFModel_SPARQLLimited::update() adding st:%s \n", st.toString().c_str() ));
    }

    delete m_AP;
    m_AP = AP;
    m_version = m_delegate->getVersion();


}
