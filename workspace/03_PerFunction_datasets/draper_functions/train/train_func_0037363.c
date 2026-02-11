next_node(p_node)


p_node_t p_node;
{

 if (p_node->p_right != NULL)
    return min_leaf(p_node->p_right);


 while (p_node->p_parent!=NULL && p_node->p_parent->p_right==p_node)
    p_node=p_node->p_parent;
 return p_node->p_parent;
}
