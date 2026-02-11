entryptr()
{
    Entry *entry = new Entry();
    entry->setName(mEntry.name());
    entry->setAuthor(mEntry.author());
    entry->setCategory(mEntry.category());
    entry->setLicense(mEntry.license());
    entry->setSummary(mEntry.summary());
    entry->setVersion(mEntry.version());
    entry->setRelease(mEntry.release());
    entry->setReleaseDate(mEntry.releaseDate());
    entry->setPayload(mEntry.payload());
    entry->setPreview(mEntry.preview());
    entry->setRating(mEntry.rating());
    entry->setDownloads(mEntry.downloads());
    entry->setInstalledFiles(mEntry.installedFiles());
    entry->setIdNumber(mEntry.idNumber());
    return entry;
}
