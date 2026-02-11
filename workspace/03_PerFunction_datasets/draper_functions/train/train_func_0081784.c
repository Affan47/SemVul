mmlCheckChildType( QwtMml::NodeType parent_type, QwtMml::NodeType child_type,
                               QString *error_str )
{
    if ( parent_type == QwtMml::UnknownNode || child_type == QwtMml::UnknownNode )
        return true;

    const QwtMmlNodeSpec *child_spec = mmlFindNodeSpec( child_type );
    const QwtMmlNodeSpec *parent_spec = mmlFindNodeSpec( parent_type );

    Q_ASSERT( parent_spec != 0 );
    Q_ASSERT( child_spec != 0 );

    QString allowed_child_types( parent_spec->child_types );

    if ( allowed_child_types.isNull() )
        return true;

    QString child_type_str = QString( " " ) + child_spec->type_str + " ";
    if ( !allowed_child_types.contains( child_type_str ) )
    {
        if ( error_str != 0 )
            *error_str = QString( "illegal child " )
                         + child_spec->type_str
                         + " for parent "
                         + parent_spec->type_str;
        return false;
    }

    return true;
}
