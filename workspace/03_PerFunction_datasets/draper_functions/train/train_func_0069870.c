embedded_files() const
{
    if (d->is_locked) {
        return std::vector<embedded_file *>();
    }

    if (d->embedded_files.empty() && d->doc->getCatalog()->numEmbeddedFiles() > 0) {
        const int num = d->doc->getCatalog()->numEmbeddedFiles();
        d->embedded_files.resize(num);
        for (int i = 0; i < num; ++i) {
            EmbFile *ef = d->doc->getCatalog()->embeddedFile(i);
            d->embedded_files[i] = embedded_file_private::create(ef);
        }
    }
    return d->embedded_files;
}
