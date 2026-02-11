updateCategoryLabel(const Category::CategoryItem *category)
{
    QModelIndex cat = indexForCategory(category);
    TreeItem *item = d->getItem(cat);
    if (!item)
        return;
    item->setLabel(category->label());
    d->_htmlSynthesis.clear();
    Q_EMIT dataChanged(cat, cat);
}
