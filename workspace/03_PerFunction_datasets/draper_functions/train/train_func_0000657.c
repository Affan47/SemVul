slotDialogAccepted()
{
    AmarokConfig::setOrganizeDirectory( ui->folderCombo->currentText() );

    AmarokConfig::setIgnoreThe( m_optionsWidget->postfixThe() );
    AmarokConfig::setReplaceSpace( m_optionsWidget->replaceSpaces() );
    AmarokConfig::setVfatCompatible( m_optionsWidget->vfatCompatible() );
    AmarokConfig::setAsciiOnly( m_optionsWidget->asciiOnly() );
    AmarokConfig::setReplacementRegexp( m_optionsWidget->regexpText() );
    AmarokConfig::setReplacementString( m_optionsWidget->replaceText() );

    m_organizeCollectionWidget->onAccept();
}
