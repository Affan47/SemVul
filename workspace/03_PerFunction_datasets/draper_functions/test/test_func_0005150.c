gamgi_expat_import_id_add (char *id,
gamgi_gml *gml, unsigned int hash)
{
if (gml->id_used == 0)
  {


  gml->id_total = GAMGI_EXPAT_BOND_BASE;
  gml->id = (char *) malloc (gml->id_total * GAMGI_ENGINE_TOKEN * sizeof (char));
  gml->id_object = (gamgi_dlist **) malloc (gml->id_total * sizeof (gamgi_dlist *));
  }
else if (gml->id_used == gml->id_total)
  {


  gml->id_total *= GAMGI_EXPAT_BOND_FACTOR;
  gml->id = (char *) realloc (gml->id,
  gml->id_total * GAMGI_ENGINE_TOKEN * sizeof (char));
  gml->id_object = (gamgi_dlist **) realloc (gml->id_object,
  gml->id_total * sizeof (gamgi_dlist *));
  }


strcpy (gml->id + GAMGI_ENGINE_TOKEN * gml->id_used, id);
gml->id_object[gml->id_used] = gml->object_end;

(gml->hash)[hash] = gamgi_math_hash_add ((gml->hash)[hash],
GAMGI_INT_TO_POINTER (gml->id_used++));
}
