resizeEvent(QResizeEvent *)
{


    QList<int> sizes = d->splitter->sizes();
    const bool hasPreview = (sizes.count() == 2);

    d->splitter->resize(size());
    sizes = d->splitter->sizes();

    const bool restorePreviewWidth = hasPreview && (d->previewWidth != sizes[1]);
    if (restorePreviewWidth) {
        const int availableWidth = sizes[0] + sizes[1];
        sizes[0] = availableWidth - d->previewWidth;
        sizes[1] = d->previewWidth;
        d->splitter->setSizes(sizes);
    }
    if (hasPreview) {
        d->previewWidth = sizes[1];
    }

    if (d->progressBar->parent() == this) {

        d->progressBar->move(2, height() - d->progressBar->height() - 2);
    }
}
