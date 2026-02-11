init( const QwtMmlNode *first_row )
{
    col_widths.clear();
    row_heights.clear();

    const QwtMmlNode *mtr = first_row;
    for ( ; mtr != 0; mtr = mtr->nextSibling() )
    {

        Q_ASSERT( mtr->nodeType() == MtrNode );

        int col_cnt = 0;
        const QwtMmlNode *mtd = mtr->firstChild();
        for ( ; mtd != 0; mtd = mtd->nextSibling(), ++col_cnt )
        {

            Q_ASSERT( mtd->nodeType() == MtdNode );

            QRect mtdmr = mtd->myRect();

            if ( col_cnt == col_widths.count() )
                col_widths.append( mtdmr.width() );
            else
                col_widths[col_cnt] = qMax( col_widths[col_cnt], mtdmr.width() );
        }

        row_heights.append( mtr->myRect().height() );
    }
}
