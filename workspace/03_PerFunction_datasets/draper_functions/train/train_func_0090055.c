deleted_from_database()
{
#if defined(DEBUG)
    printf("ED4_text_terminal::deleted_from_database (%p)\n", this);
#endif
    ED4_terminal::deleted_from_database();


    if (parent->is_name_manager()) {
#if defined(DEBUG)
        printf("- Deleting name terminal\n");
#endif
        ED4_name_manager *name_man = parent->to_name_manager();
        flag.deleted               = 1;
        name_man->delete_requested_by_child();
    }
    else if (parent->is_sequence_manager()) {
#if defined(DEBUG)
        printf("- Deleting sequence terminal\n");
#endif
        ED4_sequence_manager *seq_man = parent->to_sequence_manager();
        flag.deleted                  = 1;
        seq_man->delete_requested_by_child();
    }
    else {
        e4_assert(0);
    }
}
