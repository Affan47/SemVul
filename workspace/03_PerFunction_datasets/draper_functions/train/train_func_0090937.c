ml_print(modelline_t *ml, FILE *fd, const param_t *p)
{
    int row;
    ml_node_t *node;

    for (row = 0; row < nrow(ml, p); row++) {
        for (node = ml->line; node; node = node->next) {
            switch (node->type) {
            case ML_LITERAL:
            case ML_WHITESPACE:
                fputs(node->u.l.s, fd);
                break;
            case ML_PARAM:
                print_param_node(node, row, fd, p);
                break;
            default:
                assert(0);
            }
        }
    }
}
