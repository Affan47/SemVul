onAskForShowHideSignal(VisuNodeArray *nodeArray, gboolean *redraw,
				   gpointer data _U_)
{
  guint i, j;
  EleArr *ele;

  DBG_fprintf(stderr, "Visu NodeArray: caught the 'AskForShowHide' signal,"
	      " setting all node rendered attribute to TRUE.\n");

  for (i = 0; i < nodeArray->priv->elements->len; i++)
    for(ele = _getEleArr(nodeArray, i), j = 0; j < ele->nStoredNodes; j++)
      *redraw = visu_node_setVisibility(ele->nodes + j, TRUE) || *redraw;
  DBG_fprintf(stderr, "             - returned redraw value : %d.\n", *redraw);
}
