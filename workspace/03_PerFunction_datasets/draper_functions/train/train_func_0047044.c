paint( QPainter* painter,
		 const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
	if (index.column() != 0)
		return QStyledItemDelegate::paint(painter, option, index);

	QVariant displayData = index.data(Qt::UserRole);
	QString prstring=displayData.toString();

	QStyledItemDelegate::paint(painter, option, index);


	QRect rect=option.rect;

	QStringList optionsList = prstring.split ('|');
	QList<KIcon> iconList;
	iconList << ( optionsList.contains("Sound")   ? KIcon("media-playback-start") : KIcon() );
	iconList << ( optionsList.contains("Popup")   ? KIcon("dialog-information")   : KIcon() );
	iconList << ( optionsList.contains("Logfile") ? KIcon("text-x-generic")       : KIcon() );
	iconList << ( optionsList.contains("Taskbar") ? KIcon("services")             : KIcon() );
	iconList << ( optionsList.contains("Execute") ? KIcon("system-run")           : KIcon() );
	if( KNotifyConfigElement::have_kttsd() )
		iconList << ( optionsList.contains("KTTS") ? KIcon("text-speak") : KIcon() );

	int mc_x=0;

	int iconWidth = option.decorationSize.width();
	int iconHeight = option.decorationSize.height();
	foreach(const KIcon &icon, iconList)
	{
		icon.paint(painter, rect.left() + mc_x + 4, rect.top() + (rect.height() - iconHeight) / 2, iconWidth, iconHeight);
		mc_x += iconWidth + 4;
	}
}
