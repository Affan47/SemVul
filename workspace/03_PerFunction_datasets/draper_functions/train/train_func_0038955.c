UnLink()
{
if ( NULL == m_links )
    {
    return;
    }

--*m_links;
if ( 0 == *m_links )
    {
    delete m_links;
    }
m_links = NULL;
}
