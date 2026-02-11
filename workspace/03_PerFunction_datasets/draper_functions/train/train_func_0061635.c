rollback_item_tree_changes()
{
  I_List_iterator<Item_change_record> it(change_list);
  Item_change_record *change;
  DBUG_ENTER("rollback_item_tree_changes");

  while ((change= it++))
    *change->place= change->old_value;

  change_list.empty();
  DBUG_VOID_RETURN;
}
