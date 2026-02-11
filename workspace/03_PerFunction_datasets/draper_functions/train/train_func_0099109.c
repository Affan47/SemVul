sizeHint() const
{
    if ( m_dirty )
        const_cast<ToolStripLayout*>( this )->calculateSize();
    return m_sizeHint;
}
