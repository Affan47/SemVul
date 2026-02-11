gui_siesta_mode_show(GtkWidget *w, gpointer dialog)
{
gint i, atom, state;
gdouble scale, x1[3], x2[3], colour[3];
gpointer button, spin;
GSList *list;
struct core_pak *core;
struct spatial_pak *spatial;
struct model_pak *model;

g_assert(dialog != NULL);

model = dialog_model(dialog);
g_assert(model != NULL);

button = dialog_child_get(dialog, "phonon_toggle");
g_assert(button != NULL);

spatial_destroy_by_label("siesta_phonons", model);

state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
if (!state)
  {
  redraw_canvas(SINGLE);
  return;
  }

spin = dialog_child_get(dialog, "phonon_scaling");
scale = SPIN_FVAL(spin);


spatial = spatial_new("siesta_phonons", SPATIAL_VECTOR, 2, TRUE, model);

atom = 0;

for (list=model->cores ; list; list=g_slist_next(list))
  {
  core = list->data;
  ARR3SET(x1, core->x);


  i = model->siesta.sorted_eig_values[model->siesta.current_animation];
  x2[0] = mesch_me_get(model->siesta.eigen_xyz_atom_mat, 3*atom, i);
  x2[1] = mesch_me_get(model->siesta.eigen_xyz_atom_mat, 3*atom+1, i);
  x2[2] = mesch_me_get(model->siesta.eigen_xyz_atom_mat, 3*atom+2, i);
  atom++;


  VEC3MUL(x2, scale);
  vecmat(model->ilatmat, x2);
  ARR3ADD(x2, x1);

  spatial_vertex_add(x2, colour, spatial);
  spatial_vertex_add(x1, colour, spatial);
  }


coords_compute(model);
redraw_canvas(SINGLE);
}
