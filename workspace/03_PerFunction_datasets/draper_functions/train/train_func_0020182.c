handle_alter_part_error(ALTER_PARTITION_PARAM_TYPE *lpt,
                             bool action_completed,
                             bool drop_partition,
                             bool frm_install,
                             bool close_table)
{
  partition_info *part_info= lpt->part_info;
  DBUG_ENTER("handle_alter_part_error");

  if (close_table)
  {


    part_info= lpt->part_info->get_clone();
    alter_close_tables(lpt, action_completed);
  }

  if (part_info->first_log_entry &&
      execute_ddl_log_entry(lpt->thd,
                            part_info->first_log_entry->entry_pos))
  {


    write_log_completed(lpt, FALSE);
    release_log_entries(part_info);
    if (!action_completed)
    {
      if (drop_partition)
      {

        push_warning_printf(lpt->thd, MYSQL_ERROR::WARN_LEVEL_WARN, 1,
                            "%s %s",
           "Operation was unsuccessful, table is still intact,",
           "but it is possible that a shadow frm file was left behind");
      }
      else
      {
        push_warning_printf(lpt->thd, MYSQL_ERROR::WARN_LEVEL_WARN, 1,
                            "%s %s %s %s",
           "Operation was unsuccessful, table is still intact,",
           "but it is possible that a shadow frm file was left behind.",
           "It is also possible that temporary partitions are left behind,",
           "these could be empty or more or less filled with records");
      }
    }
    else
    {
      if (frm_install)
      {


        push_warning_printf(lpt->thd, MYSQL_ERROR::WARN_LEVEL_WARN, 1,
                            "%s %s %s",
          "Failed during alter of partitions, table is no longer intact.",
          "The frm file is in an unknown state, and a backup",
          "is required.");
      }
      else if (drop_partition)
      {


        push_warning_printf(lpt->thd, MYSQL_ERROR::WARN_LEVEL_WARN, 1,
                            "%s %s",
              "Failed during drop of partitions, table is intact.",
              "Manual drop of remaining partitions is required");
      }
      else
      {


        push_warning_printf(lpt->thd, MYSQL_ERROR::WARN_LEVEL_WARN, 1,
                            "%s %s %s",
           "Failed during renaming of partitions. We are now in a position",
           "where table is not reusable",
           "Table is disabled by writing ancient frm file version into it");
      }
    }
  }
  else
  {
    release_log_entries(part_info);
    if (!action_completed)
    {


      ;
    }
    else
    {


      push_warning_printf(lpt->thd, MYSQL_ERROR::WARN_LEVEL_WARN, 1,"%s %s",
         "Operation was successfully completed by failure handling,",
         "after failure of normal operation");
    }
  }
  DBUG_VOID_RETURN;
}
