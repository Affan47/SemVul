exportActive()
{
    KFileDialog* d = new ExportDialog( activePreset() );
    connect( d, SIGNAL(pleaseExport(QString,QList<APG::PresetPtr>)),
          this, SLOT(savePresetsToXml(QString,QList<APG::PresetPtr>)) );
    d->exec();
}
