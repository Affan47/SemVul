fput_sem_shared_branch(FILE *fp,
		       const SemBranch *branch,
		       const Module_table *module,
		       const int current_pe,
		       Boolean opt_scalar_map)
{
    int n;

    switch (branch->kind) {
    case EMPTY:
        n = 0;
        break;
    case NODE:
        n = fput_sem_shared_node0(fp, branch->data.node, module, current_pe, opt_scalar_map);
        break;
    case LEAF:
        n = fput_sem_shared_leaf(fp, branch->data.leaf, module, current_pe, opt_scalar_map);
        break;
    default:
        fatal("kokonihakonainoniwarningdasuna");
        n = 0;
    }

    return n;
}
