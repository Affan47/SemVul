construct_retval(void *vtype)
{
  int type = v_to_type(vtype);
  const QMetaObject *mo = v_to_metaobject(vtype);
  if (mo)
    return static_cast<void*>(new QObject*(0));
  else if (type == QMetaType::Void)
    return 0;
  else if (type == qMetaTypeId<QVariant>())
    return static_cast<void*>(new QVariant());
  else if (type)
    return QMetaType::construct(type);
  return 0;
}
