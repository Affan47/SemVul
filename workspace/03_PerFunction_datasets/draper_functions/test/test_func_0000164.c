addMethod(const QByteArray& signature)
{
    int index = d->methods.size();
    d->methods.append(QMetaMethodBuilderPrivate(QMetaMethod::Method, signature));
    return QMetaMethodBuilder(this, index);
}
