slotAddFormat()
{
    bool ok = false;
    QString name = KInputDialog::getText( i18n( "New Format Preset" ), i18n( "Preset Name" ), i18n( "New Preset" ),  &ok, this );
    if( !ok )
        return;

    QString format = getParsableScheme();
    m_presetCombo->insertItem(0, name, format);
    m_presetCombo->setCurrentIndex( 0 );
    m_formatListModified = true;
}
