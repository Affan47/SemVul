operator<<( std::ostream & os, const ReceivedBundle& b )
{
    static int indent = 0;

    for( int j=0; j < indent; ++j )
        os << "  ";
    os << "{ ( ";
    if( b.TimeTag() == 1 )
        os << "immediate";
    else
        os << b.TimeTag();
    os << " )\n";

    ++indent;

    for( ReceivedBundle::const_iterator i = b.ElementsBegin();
            i != b.ElementsEnd(); ++i ){
        if( i->IsBundle() ){
            ReceivedBundle b(*i);
            os << b << "\n";
        }else{
            ReceivedMessage m(*i);
            for( int j=0; j < indent; ++j )
                os << "  ";
            os << m << "\n";
        }
    }

    --indent;

    for( int j=0; j < indent; ++j )
        os << "  ";
    os << "}";

    return os;
}
