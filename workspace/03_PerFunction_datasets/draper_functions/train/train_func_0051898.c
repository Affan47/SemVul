oc_huff_tree_occupancy(oc_huff_node *_binode,int _depth){
  if(_binode->nbits==0||_depth<=0)return 1;
  else{
    return oc_huff_tree_occupancy(_binode->nodes[0],_depth-1)+
     oc_huff_tree_occupancy(_binode->nodes[1],_depth-1);
  }
}
