createListView(QWidget* parent)
{
    FormListView* widget = new FormListView(parent);
    if( parent && parent->layout() )
        parent->layout()->addWidget(widget);
    return widget;
}
