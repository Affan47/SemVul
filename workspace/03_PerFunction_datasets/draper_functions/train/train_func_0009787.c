barrier_group_destruct(barrier_group *bgrp)
{
    int i;
    if (bgrp->group_type == type_barrier_group) {
        for (i = 0; i < bgrp->group_member_count; i++) {
            barrier_group_destruct(bgrp->barrier_group_list[i]);
        }
        free(bgrp->barrier_group_list);
    }
    else {
        free(bgrp->pe_group_list);
    }
    free(bgrp);
}
