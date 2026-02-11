gamgi_engine_create_assembly (void)
{
gamgi_assembly *old_assembly = gamgi->assembly_end, *assembly;


assembly = GAMGI_CAST_ASSEMBLY malloc (sizeof (gamgi_assembly));


assembly->text_start = NULL;
assembly->text_end = NULL;
assembly->orbital_start = NULL;
assembly->orbital_end = NULL;
assembly->bond_start = NULL;
assembly->bond_end = NULL;
assembly->atom_start = NULL;
assembly->atom_end = NULL;
assembly->direction_start = NULL;
assembly->direction_end = NULL;
assembly->plane_start = NULL;
assembly->plane_end = NULL;
assembly->group_start = NULL;
assembly->group_end = NULL;
assembly->molecule_start = NULL;
assembly->molecule_end = NULL;
assembly->cluster_start = NULL;
assembly->cluster_end = NULL;
assembly->cell_start = NULL;
assembly->cell_end = NULL;
assembly->arrow_start = NULL;
assembly->arrow_end = NULL;
assembly->shape_start = NULL;
assembly->shape_end = NULL;
assembly->graph_start = NULL;
assembly->graph_end = NULL;
assembly->assembly_start = NULL;
assembly->assembly_end = NULL;


gamgi->assembly_end = assembly;
assembly->before = old_assembly;
assembly->next = NULL;
if (old_assembly != NULL) old_assembly->next = assembly;
else gamgi->assembly_start = assembly;

return assembly;
}
