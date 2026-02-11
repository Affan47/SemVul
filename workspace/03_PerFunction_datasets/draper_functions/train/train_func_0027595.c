print_pointer_block(Block *dst)
{


    printf("block no : %d\n", dst->no);
    printf("###############maymod##################\n");
    print_array_du_semnode(dst->module, get_array_maymod(dst));

    if (dst->inner != NULL) {
	print_pointer_block_inner(dst->inner);
    }
}
