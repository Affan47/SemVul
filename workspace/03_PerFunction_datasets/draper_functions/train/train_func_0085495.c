gamgi_gtk_measure_reciprocal_ok (gamgi_object *object, gamgi_window *window)
{
gamgi_layer *layer_new;
GtkWidget *dialog = window->dialog0;
gamgi_cell *cell, *cell_new;
GtkWidget *entry;
GtkWidget *button;
const char *name;
double factor;
gamgi_bool primitive, planes;

cell = GAMGI_CAST_CELL object;


primitive = FALSE;
button = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "reciprocal_button_lattice");
if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)) == TRUE)
  {


  if (cell->model != GAMGI_PHYS_CONVENTIONAL ||
  gamgi_phys_cell_primitive (cell->lattice) == cell->lattice)
    {
    gamgi_gtk_dialog_message_create ("Error",
    "Redundant primitive lattice for non centered lattice", window);
    return;
    }
  primitive = TRUE;
  }

button = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "reciprocal_button_planes");
if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)) == TRUE)
  planes = TRUE;
else
  planes = FALSE;


button = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "reciprocal_button_bravais");
entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "reciprocal_entry_constant");
name = gtk_entry_get_text (GTK_ENTRY (entry));

if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)) == TRUE)
  {


  factor = gamgi_math_vector_mix (cell->p1, cell->p2, cell->p3);
  factor = pow (factor, 2.0/3.0);
  }
else if (gamgi_io_token_double_scan (name, &factor,
GAMGI_PHYS_RECIPROCAL_MIN, DBL_MAX) == FALSE)
  {
  gamgi_gtk_dialog_message_create ("Error", "Invalid Factor Data", window);
  return;
  }


layer_new = static_reciprocal_create (window->layer, window);

if (primitive == TRUE)
  {
  cell_new = gamgi_phys_reciprocal_primitive (cell, factor, window);
  gamgi_engine_link_cell_layer (cell_new, layer_new);
  }

cell_new = gamgi_phys_reciprocal (cell, factor, planes, window);
gamgi_engine_link_cell_layer (cell_new, layer_new);


gamgi_engine_link_layer_window (layer_new, window);
gamgi_gtk_object_layer_local (layer_new, window);
gamgi_gtk_object_focus_local (GAMGI_CAST_OBJECT layer_new, window);

gamgi_gtk_dialog_task0_remove (NULL, window);


gtk_widget_queue_draw (window->area);
}
