scriptlevel( const QwtMmlNode *child ) const
{
    int sl = QwtMmlNode::scriptlevel();

    QwtMmlNode *sub = subscript();
    QwtMmlNode *sup = superscript();

    if ( child != 0 && ( child == sup || child == sub ) )
        return sl + 1;
    else
        return sl;
}
