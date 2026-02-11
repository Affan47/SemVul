tbbt_printNode(TBBT_NODE * node, VOID(*key_dump)(VOID *,VOID *))
{

    if (node == NULL)
      {
        printf("ERROR:  null node pointer\n");
        return;
      }
    printf("node=%p, flags=%x, Lcnt=%ld, Rcnt=%ld\n", node, (unsigned)node->flags,
           (long)node->lcnt, (long)node->rcnt);
    printf("Lchild=%p, Rchild=%p, Parent=%p\n", node->Lchild, node->Rchild, node->Parent);
    if (key_dump != NULL)
      {
        (*key_dump)(node->key,node->data);
      }
    fflush(stdout);
#if 0
    printf("Lcnt=%d, Rcnt=%d\n", (int) node->lcnt, (int) node->rcnt);
    printf("*key=%d\n", (int) *(int32 *) (node->key));
    printf("Lchild=%p, Rchild=%p, Parent=%p\n", node->Lchild, node->Rchild, node->Parent);
#endif
}
