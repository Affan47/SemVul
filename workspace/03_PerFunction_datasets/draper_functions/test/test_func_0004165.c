informationWId(WId parent_id,const QString &text,
			 const QString &caption, const QString &dontShowAgainName, Options options)
{
    informationListWId(parent_id, text, QStringList(), caption, dontShowAgainName, options);
}
