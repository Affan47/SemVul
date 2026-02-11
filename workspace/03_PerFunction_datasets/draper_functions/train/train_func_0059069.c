fm_trash_or_delete_files(GtkWindow* parent, FmPathList* files)
{
    if( !fm_path_list_is_empty(files) )
    {
        gboolean all_in_trash = TRUE;
        if(fm_config->use_trash)
        {
            GList* l = fm_path_list_peek_head_link(files);
            for(;l;l=l->next)
            {
                FmPath* path = FM_PATH(l->data);
                if(!fm_path_is_trash(path))
                    all_in_trash = FALSE;
            }
        }


        if(fm_config->use_trash && !all_in_trash)
            fm_trash_files(parent, files);
        else
            fm_delete_files(parent, files);
    }
}
