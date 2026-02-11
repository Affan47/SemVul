summaryText() const
{
    if (d->m_useCheckBox)
        return d->m_summaryCheckBox->text();
    return d->m_summaryLabel->text();
}
