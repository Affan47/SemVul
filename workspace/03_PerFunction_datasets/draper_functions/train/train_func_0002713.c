debug(const QString &str)
{
	client()->debug(QString("%1: ").arg(metaObject()->className()) + str);
}
