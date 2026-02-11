mark_full_partition_used_no_parts(partition_info* part_info,
                                              uint32 part_id)
{
  DBUG_ENTER("mark_full_partition_used_no_parts");
  DBUG_PRINT("enter", ("Mark partition %u as used", part_id));
  bitmap_set_bit(&part_info->used_partitions, part_id);
  DBUG_VOID_RETURN;
}
