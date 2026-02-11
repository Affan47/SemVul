ResetColumnSizes( bool fromAutoCenter )
{
    unsigned int i;


    int psum = 0;
    for ( i=0; i<m_colWidths.size(); i++ )
        psum += m_columnProportions[i];
    int puwid = (m_pPropGrid->m_width*256) / psum;
    int cpos = 0;


    for ( i=0; i<(m_colWidths.size() - 1); i++ )
    {
        int cwid = (puwid*m_columnProportions[i]) / 256;
        cpos += cwid;
        DoSetSplitterPosition(cpos, i, false, fromAutoCenter);
    }
}
