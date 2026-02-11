createFileWidget(QWidget* parent, const QString& startDirOrVariable)
{
    FormFileWidget* widget = new FormFileWidget(parent, startDirOrVariable);
    if( parent && parent->layout() )
        parent->layout()->addWidget(widget);
    return widget;
}
