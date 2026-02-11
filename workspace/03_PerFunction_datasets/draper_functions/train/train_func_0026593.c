address_node_compare(const void *node1, const void *node2)
{unsigned int a1,a2;
 a1=((struct node *)node1)->address;
 a2=((struct node *)node2)->address;
 if (a1> a2) return 1;
 if (a1< a2) return -1;
 return 0;
}
