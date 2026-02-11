static_apply (gamgi_molecule *molecule, gamgi_window *window)
{
gamgi_layer *layer;
gamgi_molecule *molecule_new = NULL;
gamgi_dlist *atom_start;
double translate[3];
int i;


if (cache.layer == NULL)
  layer = gamgi_engine_find_layer (GAMGI_CAST_OBJECT molecule);
else
  layer = cache.layer;


atom_start = gamgi_engine_dlist_atom_object (GAMGI_CAST_OBJECT molecule, NULL);

if (cache.local == TRUE)
  gamgi_gtk_history_update (layer, layer->undo, GAMGI_ENGINE_UNDO);

gamgi_math_vector_zero (translate);
for (i = 0; i < cache.number; i++)
  {
  molecule_new = gamgi_engine_copy_molecule (molecule);
  if (cache.name[0] != '\0')
    strcpy (molecule_new->object.name, cache.name);

  gamgi_engine_link_molecule_layer (molecule_new, cache.layer);


  gamgi_chem_bond_half_clean (atom_start);

  gamgi_math_vector_add (translate, cache.shift, translate);
  gamgi_mesa_translate_molecule (molecule_new, translate);
  }


gamgi_engine_dlist_remove_all (atom_start);

return TRUE;
}
