onCompleterIndexActivated(const QModelIndex &index)
{
    if (!m_ZipModel || !m_CityModel)
        return;
    QAbstractItemModel *model = const_cast<QAbstractItemModel*>(index.model());
    const QString &zip = model->index(index.row(), ZipCountryModel::Zip).data().toString();
    const QString &city = model->index(index.row(), ZipCountryModel::City).data().toString();
    const QString &province = model->index(index.row(), ZipCountryModel::Province).data().toString();

    m_zipEdit->blockSignals(true);
    m_cityEdit->blockSignals(true);
    m_provinceCombo->blockSignals(true);
    if (m_zipEdit) {
        m_zipEdit->clearFocus();
        m_zipEdit->setText(zip.toUpper());
    }
    if (m_cityEdit) {
        m_cityEdit->clearFocus();
        m_cityEdit->setText(city.toUpper());
    }
    if (m_provinceCombo) {
        m_provinceCombo->clearFocus();
        m_provinceCombo->setCurrentIndex(m_provinceCombo->findText(province));
    }

    m_zipEdit->blockSignals(false);
    m_cityEdit->blockSignals(false);
    m_provinceCombo->blockSignals(false);
    checkData();
}
