get_new_trie_node(void)
{if(node_no>=max_no_of_nodes)
overflow("trie node");
trie_node_mem[node_no].rule=NULL;
return&trie_node_mem[node_no++];
}
