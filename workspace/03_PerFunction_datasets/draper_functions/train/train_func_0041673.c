slotAddPicture()
{

    QString defaultLoadPath = App::settings->value("Fotowall/LoadImagesDir").toString();


    QStringList picFilePaths = QFileDialog::getOpenFileNames(0, tr("Add Pictures to the Canvas"), defaultLoadPath, tr("Images (%1)").arg(App::supportedImageFormats()) );
    if (picFilePaths.isEmpty())
        return;
    App::settings->setValue("Fotowall/LoadImagesDir", QFileInfo(picFilePaths[0]).absolutePath());
    m_extCanvas->addPictureContent(picFilePaths);
    setFocusToScene();
}
