setData(const int ref, const QVariant &data, const int role)
{
    if (role!=Qt::EditRole)
        return false;
    if (ref==Form::IFormItemData::ID_CurrentUuid) {
        int id = parentItem()->valueReferences()->values(Form::FormItemValues::Value_Uuid).indexOf(data.toString());
        m_Combo->m_Combo->setCurrentIndex(id);
        onValueChanged();
    }
    return true;
}
