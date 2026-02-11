gonzo_gstate_write_sub(gonzo_ty *gp)
{
    string_ty       *filename_new;
    string_ty       *filename_old;
    static int      count;

    if (!gp->modified)
        return;
    trace(("gonzo_gstate_write_sub()\n{\n"));
    assert(gp->gstate_data);
    assert(gp->gstate_filename);
    filename_new = str_format("%s,%d", gp->gstate_filename->str_text, ++count);
    filename_old = str_format("%s,%d", gp->gstate_filename->str_text, ++count);
    if (gp->is_a_new_file)
    {
        construct_library_directory(gp);
        gonzo_become();
        undo_unlink_errok(filename_new);
        gstate_write_file(filename_new, gp->gstate_data, 0);
        commit_rename(filename_new, gp->gstate_filename);
        os_chmod(filename_new, 0644);
        gonzo_become_undo();
    }
    else
    {
        gonzo_become();
        undo_unlink_errok(filename_new);
        gstate_write_file(filename_new, gp->gstate_data, 0);
        commit_rename(gp->gstate_filename, filename_old);
        commit_rename(filename_new, gp->gstate_filename);
        commit_unlink_errok(filename_old);
        os_chmod(filename_new, 0644);
        gonzo_become_undo();
    }
    str_free(filename_new);
    str_free(filename_old);
    gp->modified = 0;
    trace(("}\n"));
}
