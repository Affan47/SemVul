is_unique (EggToolbarsModel *model,
	   EggToolbarsItem *idata)
{
  EggToolbarsItem *idata2;
  GNode *toolbar, *item;


  for(toolbar = g_node_first_child (model->priv->toolbars);
      toolbar != NULL; toolbar = g_node_next_sibling (toolbar))
    {
      for(item = g_node_first_child (toolbar);
	  item != NULL; item = g_node_next_sibling (item))
        {
	  idata2 = item->data;

	  if (idata != idata2 && strcmp (idata->name, idata2->name) == 0)
	    {
	      return FALSE;
	    }
	}
    }

  return TRUE;
}
