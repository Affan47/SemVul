fixOccurrenceReferences(QOrganizerItem* theItem, QOrganizerManager::Error* error)
{
    if (theItem->type() == QOrganizerItemType::TypeEventOccurrence
            || theItem->type() == QOrganizerItemType::TypeTodoOccurrence) {
        const QString guid = theItem->guid();
        QOrganizerItemParent instanceOrigin = theItem->detail<QOrganizerItemParent>();
        if (!instanceOrigin.originalDate().isValid()) {
            *error = QOrganizerManager::InvalidOccurrenceError;
            return false;
        }
        QOrganizerItemId parentId = instanceOrigin.parentId();
        if (!guid.isEmpty()) {
            if (!parentId.isNull()) {
                QOrganizerManager::Error tempError;
                QOrganizerItem parentItem = item(parentId, QOrganizerItemFetchHint(), &tempError);
                if (guid != parentItem.guid()
                        || !typesAreRelated(theItem->type(), parentItem.type())) {


                    *error = QOrganizerManager::InvalidOccurrenceError;
                    return false;
                }
            } else {


                foreach (const QOrganizerItem& item, d->m_idToItemHash) {
                    if (item.guid() == guid) {
                        parentId = item.id();
                        break;
                    }
                }
                if (parentId.isNull()) {

                    *error = QOrganizerManager::InvalidOccurrenceError;
                    return false;
                }
                QOrganizerManager::Error tempError;
                QOrganizerItem parentItem = item(parentId, QOrganizerItemFetchHint(), &tempError);
                if (!typesAreRelated(theItem->type(), parentItem.type())) {

                    *error = QOrganizerManager::InvalidOccurrenceError;
                    return false;
                }

                QOrganizerItemParent origin = theItem->detail<QOrganizerItemParent>();
                origin.setParentId(parentId);
                theItem->saveDetail(&origin);
            }
        } else if (!parentId.isNull()) {
            QOrganizerManager::Error tempError;
            QOrganizerItem parentItem = item(parentId, QOrganizerItemFetchHint(), &tempError);
            if (parentItem.guid().isEmpty()
                    || !typesAreRelated(theItem->type(), parentItem.type())) {

                *error = QOrganizerManager::InvalidOccurrenceError;
                return false;
            }
            theItem->setGuid(parentItem.guid());
        } else {

            *error = QOrganizerManager::InvalidOccurrenceError;
            return false;
        }
    }
    return true;
}
