setData(const int ref, const QVariant &data, const int role)
{
    Q_UNUSED(ref);
    if (!m_BaseGroup)
        return false;
    if (role==Qt::CheckStateRole) {
        if (Constants::isGroupCollapsible(m_FormItem, false)) {
            m_BaseGroup->m_Group->setChecked(data.toBool());
            m_BaseGroup->expandGroup(data.toBool());
            onValueChanged();
        }
        else if (Constants::isGroupCheckable(m_FormItem, false)) {
            m_BaseGroup->m_Group->setChecked(data.toBool());
            onValueChanged();
        }
    }
    return true;
}
