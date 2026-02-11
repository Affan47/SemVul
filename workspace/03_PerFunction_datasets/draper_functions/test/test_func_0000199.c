getLines() const
{
    QList<int> selection;

    if ( selectedLine_ >= 0 )
        selection.append( selectedLine_ );
    else if ( selectedPartial_.line >= 0 )
        selection.append( selectedPartial_.line );
    else if ( selectedRange_.startLine >= 0 )
        for ( int i = selectedRange_.startLine;
                i <= selectedRange_.endLine; i++ )
            selection.append( i );

    return selection;
}
