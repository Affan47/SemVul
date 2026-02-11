init()
{


    QString filenameLayout = m_channel->filenameLayout();

    if( filenameLayout == QLatin1String( "%default%" ) )
    {
        m_pflc->m_filenameLayoutDefault->setChecked( true );
        m_pflc->m_filenameLayoutCustom->setChecked( false );
        m_choice = 0;
    }
    else
    {
        m_pflc->m_filenameLayoutDefault->setChecked( false );
        m_pflc->m_filenameLayoutCustom->setChecked( true );
        m_pflc->m_filenameLayoutText->setText( filenameLayout );
        m_choice = 1;
    }

    connect( this, SIGNAL(okClicked()), this, SLOT(slotApply()) );
}
