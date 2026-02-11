_fm_template_insert_sorted(FmTemplate *templ, FmTemplateFile *file)
{
    FmTemplateDir *last_dir = templates_dirs;
    FmTemplateFile *last = NULL, *next;

    for(next = templ->files; next; next = next->next_in_templ)
    {
        while(last_dir && last_dir != file->dir && last_dir != next->dir)
            last_dir = last_dir->next;
        g_assert(last_dir != NULL);
        if(last_dir == file->dir)
        {
            if(next->dir == last_dir && !file->is_desktop_entry)
            {
                if(!next->is_desktop_entry)
                    break;

            }
            else
                break;
        }
        last = next;
    }
    file->next_in_templ = next;
    if(last)
        last->next_in_templ = file;
    else
        templ->files = file;
}
