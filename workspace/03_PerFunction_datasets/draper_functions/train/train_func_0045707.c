gamgi_engine_create_group (void)
{
gamgi_group *old_group = gamgi->group_end, *group;


group = GAMGI_CAST_GROUP malloc (sizeof (gamgi_group));


group->text_start = NULL;
group->text_end = NULL;
group->orbital_start = NULL;
group->orbital_end = NULL;
group->bond_start = NULL;
group->bond_end = NULL;
group->atom_start = NULL;
group->atom_end = NULL;
group->direction_start = NULL;
group->direction_end = NULL;
group->plane_start = NULL;
group->plane_end = NULL;
group->group_start = NULL;
group->group_end = NULL;


gamgi->group_end = group;
group->before = old_group;
group->next = NULL;
if (old_group != NULL) old_group->next = group;
else gamgi->group_start = group;

return group;
}
