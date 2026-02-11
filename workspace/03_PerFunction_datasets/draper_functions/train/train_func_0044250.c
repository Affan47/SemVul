checkValidity()
{
    if (!m_service->isOperationEnabled(operationName())) {
        setError(-1);
        setErrorText(i18n("Job no longer valid, operation is not enabled."));
    } else if (m_delayedDesc) {
        d->parameters = m_service->parametersFromDescription(*m_delayedDesc);
    } else {
        KConfigGroup description = m_service->operationDescription(operationName());
        QMapIterator<QString, QVariant> param(parameters());
        while (param.hasNext()) {
            param.next();
            if (!description.hasKey(param.key())) {
                setError(-1);
                setErrorText(i18n("Job no longer valid, invalid parameters."));
                break;
            }
        }
    }

    delete m_delayedDesc;
    m_delayedDesc = 0;
}
