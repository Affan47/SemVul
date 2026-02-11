_k_slotRefreshItems(const QList<QPair<KFileItem, KFileItem> >& items)
{
    QModelIndex topLeft, bottomRight;


    for ( QList<QPair<KFileItem, KFileItem> >::const_iterator fit = items.begin(), fend = items.end() ; fit != fend ; ++fit ) {
        Q_ASSERT(!fit->first.isNull());
        Q_ASSERT(!fit->second.isNull());
        const KUrl oldUrl = fit->first.url();
        const KUrl newUrl = fit->second.url();
        KDirModelNode* node = nodeForUrl(oldUrl);

        if (!node)
            continue;
        if (node != m_rootNode) {
            bool hasNewNode = false;

            if (fit->first.isDir() != fit->second.isDir()) {

                const int r = node->rowNumber();
                removeFromNodeHash(node, oldUrl);
                KDirModelDirNode* dirNode = node->parent();
                delete dirNode->m_childNodes.takeAt(r);
                node = fit->second.isDir() ? new KDirModelDirNode(dirNode, fit->second)
                       : new KDirModelNode(dirNode, fit->second);
                dirNode->m_childNodes.insert(r, node);
                hasNewNode = true;
            } else {
                node->setItem(fit->second);
            }

            if (oldUrl != newUrl || hasNewNode) {


                m_nodeHash.remove(cleanupUrl(oldUrl));
                m_nodeHash.insert(cleanupUrl(newUrl), node);
            }

            if (fit->first.mimeTypePtr()->name() != fit->second.mimeTypePtr()->name()) {
                node->setPreview(QIcon());
            }

            const QModelIndex index = indexForNode(node);
            if (!topLeft.isValid() || index.row() < topLeft.row()) {
                topLeft = index;
            }
            if (!bottomRight.isValid() || index.row() > bottomRight.row()) {
                bottomRight = index;
            }
        }
    }
#ifndef NDEBUG
    kDebug(7008) << "dataChanged(" << debugIndex(topLeft) << " - " << debugIndex(bottomRight);
#endif
    bottomRight = bottomRight.sibling(bottomRight.row(), q->columnCount(QModelIndex())-1);
    emit q->dataChanged(topLeft, bottomRight);
}
