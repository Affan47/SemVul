data(const int ref) const
{
    if (ref == IcdXml) {
        if (!d->m_IcdModel)
            return QVariant();
        ICD::IcdIO io;
        return io.icdCollectionToXml(d->m_IcdModel);
    } else if (ref==IcdCodeList) {
        if (d->m_IcdModel)
            return d->m_IcdModel->includedCodesWithDaget().join(";");
        return QVariant();
    } else if (ref==IcdLabelHtmlList) {
        if (d->m_IcdModel) {
            return d->m_IcdModel->includedLabelsToHtml();
        }
        return QVariant();
    } else if (ref==IcdLabelStringList) {
        if (d->m_IcdModel) {
            return d->m_IcdModel->includedLabels();
        }
        return QVariant();
    }
    return d->m_Data.value(ref);
}
