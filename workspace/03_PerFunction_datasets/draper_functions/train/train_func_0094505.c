setOptions(long options)
{
    d->m_caseSensitive->setChecked((d->m_enabled & KFind::CaseSensitive) && (options & KFind::CaseSensitive));
    d->m_wholeWordsOnly->setChecked((d->m_enabled & KFind::WholeWordsOnly) && (options & KFind::WholeWordsOnly));
    d->m_fromCursor->setChecked((d->m_enabled & KFind::FromCursor) && (options & KFind::FromCursor));
    d->m_selectedText->setChecked((d->m_enabled & KFind::SelectedText) && (options & KFind::SelectedText));
    d->m_regExp->setChecked((d->m_enabled & KFind::RegularExpression) && (options & KFind::RegularExpression));
    d->m_findLinksOnly->setChecked((d->m_enabled & KHTMLPart::FindLinksOnly) && (options & KHTMLPart::FindLinksOnly));
}
