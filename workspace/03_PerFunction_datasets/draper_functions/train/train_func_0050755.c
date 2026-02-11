ompi_group_dump (ompi_group_t* group)
{
    int i;
    int new_rank;

    i=0;
    printf("Group Proc Count: %d\n",group->grp_proc_count);
    printf("Group My Rank: %d\n",group->grp_my_rank);
    if (OMPI_GROUP_IS_SPORADIC(group)) {
        ompi_group_translate_ranks( group,1,&group->grp_my_rank,
                                    group->grp_parent_group_ptr,
                                    &new_rank);
        printf("Rank in the parent group: %d\n",new_rank);
        printf("The Sporadic List Length: %d\n",
               group->sparse_data.grp_sporadic.grp_sporadic_list_len);
        printf("Rank First       Length\n");
        for(i=0 ; i<group->sparse_data.grp_sporadic.grp_sporadic_list_len ; i++) {
            printf("%d               %d\n",
                   group->sparse_data.grp_sporadic.grp_sporadic_list[i].rank_first,
                   group->sparse_data.grp_sporadic.grp_sporadic_list[i].length);
        }
    }
    else if (OMPI_GROUP_IS_STRIDED(group)) {
        ompi_group_translate_ranks( group,1,&group->grp_my_rank,
                                    group->grp_parent_group_ptr,
                                    &new_rank);
        printf("Rank in the parent group: %d\n",new_rank);
        printf("The Offset is: %d\n",group->sparse_data.grp_strided.grp_strided_offset);
        printf("The Stride is: %d\n",group->sparse_data.grp_strided.grp_strided_stride);
        printf("The Last Element is: %d\n",
               group->sparse_data.grp_strided.grp_strided_last_element);
    }
    else if (OMPI_GROUP_IS_BITMAP(group)) {
        ompi_group_translate_ranks( group,1,&group->grp_my_rank,
                                    group->grp_parent_group_ptr,
                                    &new_rank);
        printf("Rank in the parent group: %d\n",new_rank);
        printf("The length of the bitmap array is: %d\n",
               group->sparse_data.grp_bitmap.grp_bitmap_array_len);
        for (i=0 ; i<group->sparse_data.grp_bitmap.grp_bitmap_array_len ; i++) {
            printf("%d\t",group->sparse_data.grp_bitmap.grp_bitmap_array[i]);
        }
    }
    printf("*********************************************************\n");
    return OMPI_SUCCESS;
}
