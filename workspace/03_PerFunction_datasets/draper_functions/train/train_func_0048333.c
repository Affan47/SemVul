shouldPruneNode(NodeImpl *node)
{
    if (!node)
        return false;

    RenderObject *renderer = node->renderer();
    if (!renderer)
        return true;

    if (node->hasChildNodes())
        return false;

    if (node->rootEditableElement() == node)
        return false;

    if (renderer->isBR() || renderer->isReplaced())
        return false;

    if (node->isTextNode()) {
        TextImpl *text = static_cast<TextImpl *>(node);
        if (text->length() == 0)
            return true;
        return false;
    }

    if (!node->isHTMLElement())
        return false;

    if (node->id() == ID_BODY)
        return false;

    if (!node->isContentEditable())
        return false;

    return true;
}
