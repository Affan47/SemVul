trace_string(
                      SuffixTree*    tree,

                      NODE*           node,

                      PATH            str,

                      int32_t*       edge_pos,

                      int32_t*       chars_found,

                      SKIP_TYPE       type)
{


   int      search_done = 0;


   int32_t edge_chars_found;

   *chars_found = 0;

   while(search_done == 0) {
      *edge_pos        = 0;
      edge_chars_found = 0;
      node = trace_single_edge(tree, node, str, edge_pos, &edge_chars_found, type, &search_done);
      str.begin       += edge_chars_found;
      *chars_found    += edge_chars_found;
   }
   return node;
}
