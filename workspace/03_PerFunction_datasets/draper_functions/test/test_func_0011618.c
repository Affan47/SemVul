updateIcons(const KFileItemList& items)
{
    if (items.isEmpty()) {
        return;
    }

    applyCutItemEffect(items);

    KFileItemList orderedItems = items;
    orderItems(orderedItems);

    foreach (const KFileItem& item, orderedItems) {
        m_pendingItems.append(item);
    }

    if (m_previewShown) {
        createPreviews(orderedItems);
    } else {
        startMimeTypeResolving();
    }
}
