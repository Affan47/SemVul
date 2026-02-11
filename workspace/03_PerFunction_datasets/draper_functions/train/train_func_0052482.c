setHasSelection(bool hasSelection)
{
    if (hasSelection) d->m_enabled |= KFind::SelectedText;
    else d->m_enabled &= ~KFind::SelectedText;
    d->m_selectedText->setEnabled( hasSelection );
    if ( !hasSelection )
    {
        d->m_selectedText->setChecked( false );
        slotSelectedTextToggled( hasSelection );
    }
}
