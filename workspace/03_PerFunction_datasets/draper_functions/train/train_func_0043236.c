currentUuid() const
{
    if (m_Item) {
        if (m_Item->itemData()) {
            QVariant result = m_Item->itemData()->data(Form::IFormItemData::ID_CurrentUuid);
            return result;
        }
    }
    return QVariant();
}
