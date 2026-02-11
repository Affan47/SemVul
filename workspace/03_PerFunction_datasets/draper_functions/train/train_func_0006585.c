parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    KDEPrivate::AppNode *node = static_cast<KDEPrivate::AppNode*>(index.internalPointer());
    if (node->parent->parent) {
        int id = node->parent->parent->children.indexOf(node->parent);

        if (id >= 0 && id < node->parent->parent->children.count())
           return createIndex(id, 0, node->parent);
        else
            return QModelIndex();
    }
    else
        return QModelIndex();
}
