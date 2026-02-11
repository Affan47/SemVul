fetchForms(const QUrl &url) const
{
    QList<Form> forms;
    foreach (const Form &form, m_forms)
        if (form.url == url)
            forms.append(form);
#ifdef AUTOFILL_DEBUG
    qDebug() << "AutoFillManager::" << __FUNCTION__ << url << m_forms.count() << "found:" << forms.count();
#endif
    return forms;
}
