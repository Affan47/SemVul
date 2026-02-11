sendOpenUri(const QString &uri, const QString &profile) const
{
	QDBusInterface(d->dbusName(profile), "/Main", PSIDBUSMAINIF).call(QDBus::NoBlock,
			"openURI", uri);
	return true;


	return false;
}
