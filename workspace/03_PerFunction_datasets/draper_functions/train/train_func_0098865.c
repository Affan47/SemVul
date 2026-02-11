hasLoadListener(SVGElement* node)
{
    Node* currentNode = node;
    while (currentNode && currentNode->isElementNode()) {
        QList<RegisteredEventListener> *list = static_cast<Element*>(currentNode)->localEventListeners();
        if (list) {
            QList<RegisteredEventListener>::Iterator end = list->end();
            for (QList<RegisteredEventListener>::Iterator it = list->begin(); it != end; ++it)
                if ((*it).useCapture || (*it).eventName.id() == EventImpl::LOAD_EVENT)
                    return true;


        }
        currentNode = currentNode->parentNode();
    }

    return false;
}
