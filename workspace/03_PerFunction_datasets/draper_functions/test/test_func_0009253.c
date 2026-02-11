lpgaccess(int state_no, int item_no)
{
    int i;

    BOOLEAN end_node;

    struct node *access_root,
                *head,
                *tail,
                *q,
                *p,
                *s;


    access_root = Allocate_node();
    access_root -> value = state_no;
    access_root -> next = NULL;

    for (i = item_table[item_no].dot; i > 0; i--)
    {
        head = access_root;
        access_root = NULL;
        for (p = head; p != NULL; tail = p, p = p -> next)
        {


            for (end_node = ((s = in_stat[p -> value]) == NULL);
                 ! end_node;
                 end_node = (s == in_stat[p -> value]))
            {
                s = s -> next;

                q = Allocate_node();
                q -> value = s -> value;
                q -> next = access_root;
                access_root = q;
            }
        }

        free_nodes(head, tail);
     }

     return(access_root);
}
