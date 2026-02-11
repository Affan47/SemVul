buildCatalog()
{
	QList<Directory> memDirs;
	int size = gSettings->beginReadArray("directories");
	for (int i = 0; i < size; ++i)
	{
		gSettings->setArrayIndex(i);
		Directory tmp;
		tmp.name = gSettings->value("name").toString();
		tmp.types = gSettings->value("types").toStringList();
		tmp.indexDirs = gSettings->value("indexDirs", false).toBool();
		tmp.indexExe = gSettings->value("indexExes", false).toBool();
		tmp.depth = gSettings->value("depth", 100).toInt();
		memDirs.append(tmp);
	}
	gSettings->endArray();

	if (memDirs.count() == 0)
	{
		memDirs = platform->getDefaultCatalogDirectories();
	}

	QHash<uint, PluginInfo> pluginsInfo = plugins->getPlugins();
	int totalItems = memDirs.count() + pluginsInfo.count();
	int currentItem = 0;

	for (; currentItem < memDirs.count(); ++currentItem)
	{
		emit(catalogIncrement(100.0f * (currentItem+1) / totalItems));
		QString cur = platform->expandEnvironmentVars(memDirs[currentItem].name);
		indexDirectory(cur, memDirs[currentItem].types, memDirs[currentItem].indexDirs, memDirs[currentItem].indexExe, memDirs[currentItem].depth);
	}

	foreach(PluginInfo info, pluginsInfo)
	{
		emit(catalogIncrement(100.0f * (currentItem+1) / totalItems));
		if (info.loaded)
		{
			QList<CatItem> items;
			info.obj->msg(MSG_GET_CATALOG, (void*)&items);
			foreach(CatItem item, items)
			{
				if (currentCatalog != NULL)
				{
					item.usage = currentCatalog->getUsage(item.fullPath);
				}
				catalog->addItem(item);
			}
		}
		++currentItem;
	}

	emit(catalogIncrement(0.0));
}
