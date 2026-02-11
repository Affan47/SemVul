obj_get_weight (sc_gameref_t game, sc_int object)
{
  const sc_prop_setref_t bundle = gs_get_bundle (game);
  sc_vartype_t vt_key[3];
  sc_int weight, count;


  if (obj_is_static (game, object))
    return 0;


  vt_key[0].string = "Objects";
  vt_key[1].integer = object;
  vt_key[2].string = "SizeWeight";
  count = prop_get_integer (bundle, "I<-sis", vt_key) % OBJ_DIMENSION_DIVISOR;


  weight = 1;
  for (; count > 0; count--)
    weight *= OBJ_DIMENSION_MULTIPLE;


  if (obj_is_container (game, object) || obj_is_surface (game, object))
    {
      sc_int other;


      for (other = 0; other < gs_object_count (game); other++)
        {
          if ((gs_object_position (game, other) == OBJ_IN_OBJECT
               || gs_object_position (game, other) == OBJ_ON_OBJECT)
              && gs_object_parent (game, other) == object)
            {
              weight += obj_get_weight (game, other);
            }
        }
    }

  if (obj_trace)
    sc_trace ("Object: object %ld is weight %ld\n", object, weight);


  return weight;
}
