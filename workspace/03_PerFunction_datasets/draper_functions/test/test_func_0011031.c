init()
{
    setParent( m_vbox );
    show();
    m_hint = new QLabel( m_vbox );

    m_hint->setFocusPolicy( Qt::NoFocus );
    QFont font;
    font.setPointSize( font.pointSize() - 2);
    m_hint->setFont( font );
}
