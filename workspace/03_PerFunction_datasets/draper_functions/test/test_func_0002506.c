visu_node_array_switchNumber(VisuNodeArray *nodeArray, guint from, guint to)
{
  VisuNode *nodeFrom, *nodeTo;

  if (from == to)
    return FALSE;

  nodeFrom = _getFromId(&nodeArray->priv->nodeTable, from);
  nodeTo   = _getFromId(&nodeArray->priv->nodeTable, to);
  _setAtId(&nodeArray->priv->nodeTable, from, nodeTo);
  _setAtId(&nodeArray->priv->nodeTable, to, nodeFrom);
  nodeFrom->number = to;
  nodeTo->number   = from;
  return TRUE;
}
