read_node(struct dep_dic* ddic, struct dep_node* node, int* offset)
{
  int i;
  node->nr_branch = anthy_dic_ntohl(*(int*)&ddic->file_ptr[*offset]);
  *offset += sizeof(int);

  node->branch = malloc(sizeof(struct dep_branch) * node->nr_branch);
  for (i = 0; i < node->nr_branch; ++i) {
    read_branch(ddic, &node->branch[i], offset);
  }
}
