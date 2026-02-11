gamgi_engine_create_bond (void)
{
gamgi_bond *old_bond = gamgi->bond_end, *bond;


bond = GAMGI_CAST_BOND malloc (sizeof (gamgi_bond));


bond->text_start = NULL;
bond->text_end = NULL;
bond->orbital_start = NULL;
bond->orbital_end = NULL;


gamgi->bond_end = bond;
bond->before = old_bond;
bond->next = NULL;
if (old_bond != NULL) old_bond->next = bond;
else gamgi->bond_start = bond;

return bond;
}
