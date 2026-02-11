analysis_show(struct model_pak *model)
{
g_assert(model != NULL);


model->picture_active = NULL;


sysenv.refresh_dialog = TRUE;
redraw_canvas(SINGLE);
}
