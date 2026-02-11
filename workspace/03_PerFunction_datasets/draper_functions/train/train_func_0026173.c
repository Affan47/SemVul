print_stree(void)
{
    printf("\n\n---------------------------------\n\n");

    if(s_root == NULL) {
        printf("Uninitialized tree\n\n");
        return;
    }

    int print_branchs[10] = {0};

    __print_stree(s_root, 0, print_branchs);

    printf("\n\n---------------------------------\n\n");
}
