ST_FindSubstring(

                      SuffixTree*    tree,

                      char*  W,

                      int32_t        P)
{


   NODE* node   = find_son(tree, tree->root, W[0]);
   int32_t k,j = 0, node_label_end;


   while(node!=0) {
      k=node->edge_label_start;
      node_label_end = get_node_label_end(tree,node);


      while(j<P && k<=node_label_end && tree->tree_string[k] == W[j]) {
         j++;
         k++;
      }


      if(j == P) {

         return node->path_position;
      }
      else if(k > node_label_end)

         node = find_son(tree, node, W[j]);
      else {

         return CONTAINER_ERROR_NOTFOUND;
      }
   }
   return CONTAINER_ERROR_NOTFOUND;
}
