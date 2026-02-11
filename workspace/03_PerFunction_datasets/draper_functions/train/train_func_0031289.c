_evas_textblock_cursor_break_paragraph(Evas_Textblock_Cursor *cur,
                              Evas_Object_Textblock_Node_Format *fnode)
{
   Evas_Object_Textblock *o;
   Evas_Object_Textblock_Node_Text *n;

   if (!cur) return;
   o = (Evas_Object_Textblock *)(cur->obj->object_data);

   n = _evas_textblock_node_text_new();
   o->text_nodes = _NODE_TEXT(eina_inlist_append_relative(
                   EINA_INLIST_GET(o->text_nodes),
                   EINA_INLIST_GET(n),
                   EINA_INLIST_GET(cur->node)));

   if (cur->node)
     {
        Evas_Object_Textblock_Node_Format *nnode;
        size_t len, start;
        const Eina_Unicode *text;


        nnode  = _NODE_FORMAT(EINA_INLIST_GET(fnode)->next);
        if (nnode && (nnode->text_node == cur->node))
          {
             n->format_node = nnode;
             nnode->offset--;

             while (nnode && (nnode->text_node == cur->node))
               {
                  nnode->text_node = n;
                  nnode = _NODE_FORMAT(EINA_INLIST_GET(nnode)->next);
               }
          }
        else
          {
             n->format_node = fnode;
          }


        start = cur->pos + 1;
        len = eina_ustrbuf_length_get(cur->node->unicode) - start;
        if (len > 0)
          {
             text = eina_ustrbuf_string_get(cur->node->unicode);
             eina_ustrbuf_append_length(n->unicode, text + start, len);
             eina_ustrbuf_remove(cur->node->unicode, start, start + len);
             cur->node->dirty = EINA_TRUE;
          }
     }
   else
     {
        fnode = o->format_nodes;
        if (fnode)
          {
             fnode = _NODE_FORMAT(EINA_INLIST_GET(fnode)->last);
          }
        n->format_node = fnode;
     }
}
