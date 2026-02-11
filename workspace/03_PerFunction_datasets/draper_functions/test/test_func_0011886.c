importFromData( std::istream& iss, PD_DocumentRDFHandle rdf, PD_DocumentRange * pDocRange )
{
#ifdef WITH_EVOLUTION_DATA_SERVER

    std::string vcard = StreamToString( iss );
    UT_DEBUGMSG(("trying to get card for data:%s\n", vcard.c_str() ));
    if( EVCard* c = e_vcard_new_from_string( vcard.c_str() ) )
    {
        std::string textrep = "";
        typedef std::list< const char* > charplist_t;
        charplist_t textreplist;
        textreplist.push_back( EVC_EMAIL );
        textreplist.push_back( EVC_FN );
        textreplist.push_back( EVC_NICKNAME );
        textreplist.push_back( EVC_UID );
        for( charplist_t::iterator iter = textreplist.begin();
             iter != textreplist.end(); ++iter )
        {
            textrep = get( c, *iter );
            if( !textrep.empty() )
                break;
        }
        UT_DEBUGMSG(("have card!\n"));

        std::string fn    = get( c, EVC_FN );
        std::string uid   = get( c, EVC_UID );
        std::string xmlid = rdf->makeLegalXMLID( fn + "_" + uid );
        std::string email = get( c, EVC_EMAIL );
        UT_DEBUGMSG(("uid:%s xmlid:%s\n", uid.c_str(), xmlid.c_str() ));

        m_name  = fn;
        m_nick  = get( c, EVC_NICKNAME );
        m_email = email;
        m_phone = get( c, EVC_TEL );
        m_jabberID = get( c, EVC_X_JABBER );


        std::string uuid = "http://abicollab.net/rdf/foaf#" + uid;
        m_linkingSubject = PD_URI( uuid );
        XAP_Frame* lff = XAP_App::getApp()->getLastFocussedFrame();
        if(lff)
        {


        }


        PD_DocumentRDFMutationHandle m = rdf->createMutation();
        importFromDataComplete( iss, rdf, m, pDocRange );
        m->commit();
    }
#else
	UT_UNUSED(iss);
	UT_UNUSED(rdf);
	UT_UNUSED(pDocRange);
#endif
}
