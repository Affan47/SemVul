registerPlayGrounds()
{
  const QStringList list = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "pics/*.theme" ));

  foreach(const QString &theme, list)
  {
    QFile layoutFile(theme);
    if (layoutFile.open(QIODevice::ReadOnly))
    {
      QDomDocument layoutDocument;
      if (layoutDocument.setContent(&layoutFile))
      {
        QString desktop = layoutDocument.documentElement().attribute(QLatin1String( "desktop" ));
        KConfig c( KStandardDirs::locate("appdata", QLatin1String( "pics/" ) ) + desktop);
        KConfigGroup cg = c.group("KTuberlingTheme");
        QString gameboard = layoutDocument.documentElement().attribute(QLatin1String( "gameboard" ));
        QPixmap pixmap(200,100);
        pixmap.fill(Qt::transparent);
        playGroundPixmap(gameboard,pixmap);
        m_topLevel->registerGameboard(cg.readEntry("Name"), theme, pixmap);
      }
    }
  }
}
