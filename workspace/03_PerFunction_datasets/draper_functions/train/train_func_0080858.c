_k_togglePreview(bool on)
{
    if (on) {
        viewKind = viewKind | KFile::PreviewContents;
        if (preview == 0) {
            preview = new KFileMetaPreview(parent);
            actionCollection->action("preview")->setChecked(true);
            splitter->addWidget(preview);
        }

        preview->show();

        QMetaObject::invokeMethod(parent, "_k_assureVisibleSelection", Qt::QueuedConnection);
        if (itemView != 0) {
            const QModelIndex index = itemView->selectionModel()->currentIndex();
            if (index.isValid()) {
                _k_triggerPreview(index);
            }
        }
    } else if (preview != 0) {
        viewKind = viewKind & ~KFile::PreviewContents;
        preview->hide();
    }
}
