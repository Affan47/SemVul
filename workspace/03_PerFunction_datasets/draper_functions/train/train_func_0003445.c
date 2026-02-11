availableTranslations()
{
	VarList langs;


	langs.set("en", "English");


	QStringList dirs = TranslationManager::translationDirs();
	for(QStringList::Iterator it = dirs.begin(); it != dirs.end(); ++it) {
		if(!QFile::exists(*it))
			continue;
		QDir d(*it);
		QStringList entries = d.entryList();
		for(QStringList::Iterator it2 = entries.begin(); it2 != entries.end(); ++it2) {
			if(*it2 == "." || *it2 == "..")
				continue;

			QString str = *it2;

			if(str.left(4) != "psi_")
				continue;
			int n = str.find('.', 4);
			if(n == -1)
				continue;
			if(str.mid(n) != ".qm")
				continue;
			QString lang = str.mid(4, n-4);


			QString name = QString("[") + str + "]";
			QTranslator t(0);
			if(!t.load(str, *it))
				continue;


			QString s = t.translate("@default", "language_name");
			if(!s.isEmpty())
				name = s;

			langs.set(lang, name);
		}
	}

	return langs;
}
