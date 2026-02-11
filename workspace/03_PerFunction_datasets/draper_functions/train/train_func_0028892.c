siesta_phonon_stop(GtkWidget *w, gpointer dialog)
{
struct model_pak *model;

g_assert(dialog != NULL);
model = dialog_model(dialog);
g_assert(model != NULL);


model->pulse_direction = 0;
model->pulse_count = 0;
model->phonon_movie = FALSE;
}
