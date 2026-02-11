setupData(KConfigSkeleton * aconfig)
{

    KConfig * config = aconfig->config();
    KConfigGroup group = config->group("General");
    QString initialGroup = group.readEntry("Layout_file");


    kcfg_Layout->hide();


    getNewButton->hide();


    KMahjonggLayout tile;


    QStringList tilesAvailable = KGlobal::dirs()->findAllResources("kmahjongglayout", QString("*.desktop"), KStandardDirs::Recursive);
    tilesAvailable.sort();
    QString namestr("Name");
    int numvalidentries = 0;
    for (int i = 0; i < tilesAvailable.size(); ++i)
    {
        KMahjonggLayout * aset = new KMahjonggLayout();
        QString atileset = tilesAvailable.at(i);
        if (aset->load(atileset)) {
            layoutMap.insert(aset->authorProperty(namestr), aset);
            layoutList->addItem(aset->authorProperty(namestr));

            if (atileset==initialGroup) {

                layoutList->setCurrentRow(numvalidentries);
                layoutChanged();
            }
            ++numvalidentries;
        } else {
            delete aset;
        }
    }

    connect(layoutList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(layoutChanged()));
}
