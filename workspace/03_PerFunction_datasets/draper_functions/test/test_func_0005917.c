selectedPresetName() const
{
    const QString currentText = eqPresets->currentText();
    const int index = EqualizerPresets::eqGlobalTranslatedList().indexOf( currentText );
    if( index < 0 )
        return currentText;

    return EqualizerPresets::eqGlobalList().at( index );
}
