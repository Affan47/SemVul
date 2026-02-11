sync_barrier_group_upward(int count, barrier_transfer_set *bt_set,
				   barrier_group *bgrp)
{
    int i;
    if (bgrp->group_type == type_barrier_group) {
        for (i = 0; i < bgrp->group_member_count; i++) {
            count = sync_barrier_group_upward(count, bt_set,
						   bgrp->barrier_group_list[i]);
        }
        for (i = 1; i < bgrp->group_member_count; i++) {
            count = sync_group_to_group(count, bt_set, bgrp->barrier_group_list[i],
					bgrp->barrier_group_list[0]);
        }
    }
    else {
        for (i = 0; i < bgrp->group_member_count; i++) {
            count = sync_PE_to_PE(count, bt_set, bgrp->pe_group_list[i],
				  bgrp->pe_group_list[0]);
        }
    }
    return count;
}
