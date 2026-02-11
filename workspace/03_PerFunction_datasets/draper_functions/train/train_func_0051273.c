pr_nt_elem_node(FILE *fp, Nt_elem *elem)
{

    fprintf(fp, "   nt_element %d {\n", elem->entry);

    switch(elem->kind) {
    case KIND_VAR:
        fprintf(fp, "     V%d\n", elem->data.v->entry);
        break;

    case KIND_ARRAY:
        pr_nt_elem_array(fp, elem);
        break;

    default:
        break;
    }

    fprintf(fp, "   }\n");
}
