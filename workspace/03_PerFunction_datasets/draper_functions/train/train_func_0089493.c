setDynamicDataValue(const char *name, const QVariant &val, UserDynamicData::DynamicDataType t)
{
    Q_UNUSED(t);

    if (!val.isValid())
        return;
    if (!d->m_Editable)
        return;


    if ((val.isNull()) ||
         (((val.type() == QVariant::String) || (val.type() == QVariant::StringList))
           && (val.toString().isEmpty()))) {
        if (!d->m_DynamicData.keys().contains(name))
            return;
    }

    if (!d->m_DynamicData.keys().contains(name)) {
        UserDynamicData *data = new UserDynamicData();
        data->setName(name);
        data->setUserUuid(uuid());
        d->m_DynamicData.insert(name,data);
    }
    UserDynamicData *data = d->m_DynamicData[name];
    data->setValue(val);


}
