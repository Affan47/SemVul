Add_layer(T_List_of_pages *list, byte layer)
{
  T_Page * source_page;
  T_Page * new_page;
  byte * new_image;
  int i;

  source_page = list->Pages;

  if (list->Pages->Nb_layers == MAX_NB_LAYERS)
    return 1;


  if (layer > list->Pages->Nb_layers)
    layer = list->Pages->Nb_layers;


  new_image = New_layer(list->Pages->Height*list->Pages->Width);
  if (! new_image)
  {
    Error(0);
    return 1;
  }

  new_page = realloc(source_page, sizeof(T_Page)+(list->Pages->Nb_layers+1)*sizeof(byte *));
  if (!new_page)
  {
    Error(0);
    return 1;
  }
  if (new_page != source_page)
  {


    new_page->Prev->Next = new_page;
    new_page->Next->Prev = new_page;
    list->Pages = new_page;
  }
  list->Pages->Nb_layers++;


  for (i=list->Pages->Nb_layers-1; i>layer ; i--)
  {
    new_page->Image[i]=new_page->Image[i-1];
  }
  new_page->Image[layer]=new_image;

  memset(new_image, Main_backups->Pages->Transparent_color, list->Pages->Height*list->Pages->Width);


  {
    dword layers_before;
    dword layers_after;
    dword *visible_layers_flag;


    if (list == Main_backups)
    {
      visible_layers_flag = &Main_layers_visible;
      Main_current_layer = layer;
    }
    else
    {
      visible_layers_flag = &Spare_layers_visible;
      Spare_current_layer = layer;
    }


    layers_before = ((1<<layer)-1) & *visible_layers_flag;
    layers_after = (*visible_layers_flag & (~layers_before))<<1;
    *visible_layers_flag = (1<<layer) | layers_before | layers_after;
  }


  return 0;
}
