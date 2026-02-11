isPointInsideSelection(int x, int y)
{

  if (d->editor_context.m_selection.state() == Selection::CARET)
    return false;
  if (!xmlDocImpl()->renderer())
    return false;

  khtml::RenderObject::NodeInfo nodeInfo(true, true);
  xmlDocImpl()->renderer()->layer()->nodeAtPoint(nodeInfo, x, y);
  NodeImpl *innerNode = nodeInfo.innerNode();
  if (!innerNode || !innerNode->renderer())
    return false;

  return innerNode->isPointInsideSelection(x, y, d->editor_context.m_selection);
}
