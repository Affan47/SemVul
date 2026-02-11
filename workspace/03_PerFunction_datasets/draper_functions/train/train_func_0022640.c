slotDirSizeUpdate()
{
    KIO::filesize_t totalSize = d->dirSizeJob->totalSize();
    KIO::filesize_t totalFiles = d->dirSizeJob->totalFiles();
    KIO::filesize_t totalSubdirs = d->dirSizeJob->totalSubdirs();
    d->m_sizeLabel->setText(
            i18n("Calculating... %1 (%2)\n%3, %4",
                 KIO::convertSize(totalSize),
                 totalSize,
                 i18np("1 file", "%1 files", totalFiles),
                 i18np("1 sub-folder", "%1 sub-folders", totalSubdirs)));
}
