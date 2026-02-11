invalidate()
{
    m_dirty = true;
    QLayout::invalidate();

    if ( parentWidget() )
        parentWidget()->update();
}
