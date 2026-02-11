initCurrency()
{
    if (m_currencyCode.isEmpty() || !KCurrencyCode::isValid(m_currencyCode)) {
        m_currencyCode = KLocale::defaultCurrencyCode();
    }

    if (!m_currency || m_currencyCode != m_currency->isoCurrencyCode() || !m_currency->isValid()) {
        delete m_currency;
        m_currency = new KCurrencyCode(m_currencyCode, m_language);
    }
}
