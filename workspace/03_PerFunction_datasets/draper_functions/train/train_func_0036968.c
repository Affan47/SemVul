main_save_project_from_filename(gerbv_project_t *gerbvProject, gchar *filename)
{
    project_list_t *project_list = NULL, *tmp;
    int idx;
    gchar *dirName = g_path_get_dirname (filename);

    project_list = g_new0 (project_list_t, 1);
    project_list->next = project_list;
    project_list->layerno = -1;
    project_list->filename = g_strdup(gerbvProject->path);
    project_list->rgb[0] = gerbvProject->background.red;
    project_list->rgb[1] = gerbvProject->background.green;
    project_list->rgb[2] = gerbvProject->background.blue;
    project_list->next = NULL;


    for (idx = 0; idx <= gerbvProject->last_loaded; idx++) {
	if (gerbvProject->file[idx]) {
	    tmp = g_new0 (project_list_t, 1);
	    tmp->next = project_list;
	    tmp->layerno = idx;


	    if (strncmp (dirName, gerbvProject->file[idx]->fullPathname, strlen(dirName)) == 0) {

		tmp->filename = g_strdup(gerbvProject->file[idx]->fullPathname + strlen(dirName) + 1);
	    } else {


		tmp->filename = g_strdup(gerbvProject->file[idx]->fullPathname);
	    }
	    tmp->rgb[0] = gerbvProject->file[idx]->color.red;
	    tmp->rgb[1] = gerbvProject->file[idx]->color.green;
	    tmp->rgb[2] = gerbvProject->file[idx]->color.blue;
	    tmp->inverted = gerbvProject->file[idx]->transform.inverted;
	    tmp->visible = gerbvProject->file[idx]->isVisible;

	    project_list = tmp;
	}
    }

    if (write_project_file(gerbvProject, gerbvProject->project, project_list)) {
	GERB_MESSAGE("Failed to write project\n");
    }
    project_destroy_project_list (project_list);
    g_free (dirName);
}
