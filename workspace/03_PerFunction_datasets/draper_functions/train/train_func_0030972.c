requestControl(const char *name)
{
    Q_D(QMediaImageViewerService);

    if (qstrcmp(name, QMediaImageViewerControl_iid) == 0) {
        return d->viewerControl;
    } else if (qstrcmp(name, QVideoRendererControl_iid) == 0) {
        if (!d->rendererControl) {
            d->rendererControl = new QMediaImageViewerRenderer;
            d->rendererControl->showImage(d->m_image);

            return d->rendererControl;
        }
    }
    return 0;
}
