initializeModel(const QModelIndex &parent)
{
    if (!model) {
        return;
    }
    for (int i = 0; i < model->rowCount(parent); ++i) {
        for (int j = 0; j < model->columnCount(parent); ++j) {
            const QModelIndex index = model->index(i, j, parent);
            if (index.isValid()) {
                widgetPool->findWidgets(index, optionView(index));
            }
        }


        const QModelIndex index = model->index(i, 0, parent);
        if (index.isValid() && model->hasChildren(index)) {
            initializeModel(index);
        }
    }
}
