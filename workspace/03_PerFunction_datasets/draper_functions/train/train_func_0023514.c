apAdd( PP_AttrProp* AP, const PD_URI& s, const PD_URI& p, const PD_Object& o )
{
    POCol l;
    const gchar* szName = s.toString().c_str();
    const gchar* szValue = 0;
	if( AP->getProperty( szName, szValue) )
    {
        l = decodePOCol(szValue);
    }


    l.insert( std::make_pair( p, o ));
    std::string po = encodePOCol(l);
    return AP->setProperty( szName, po.c_str() );
}
