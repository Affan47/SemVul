setImageFileName(ViewLayer::ViewID viewID, const QString & filename) {
    ViewImage * viewImage = m_viewImages.value(viewID);
    if (viewImage == NULL) return;

    viewImage->image = filename;
}
