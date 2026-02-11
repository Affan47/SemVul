GC_promote_black_lists(void)
{
    word * very_old_normal_bl = GC_old_normal_bl;
    word * very_old_stack_bl = GC_old_stack_bl;

    GC_old_normal_bl = GC_incomplete_normal_bl;
    GC_old_stack_bl = GC_incomplete_stack_bl;
    if (!GC_all_interior_pointers) {
      GC_clear_bl(very_old_normal_bl);
    }
    GC_clear_bl(very_old_stack_bl);
    GC_incomplete_normal_bl = very_old_normal_bl;
    GC_incomplete_stack_bl = very_old_stack_bl;
    GC_total_stack_black_listed = total_stack_black_listed();
    GC_VERBOSE_LOG_PRINTF(
                "%lu bytes in heap blacklisted for interior pointers\n",
                (unsigned long)GC_total_stack_black_listed);
    if (GC_total_stack_black_listed != 0) {
        GC_black_list_spacing =
                HBLKSIZE*(GC_heapsize/GC_total_stack_black_listed);
    }
    if (GC_black_list_spacing < 3 * HBLKSIZE) {
        GC_black_list_spacing = 3 * HBLKSIZE;
    }
    if (GC_black_list_spacing > MAXHINCR * HBLKSIZE) {
        GC_black_list_spacing = MAXHINCR * HBLKSIZE;


    }
}
