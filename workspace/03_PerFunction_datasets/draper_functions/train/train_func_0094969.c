vrp_meet_1 (value_range_t *vr0, value_range_t *vr1)
{
  value_range_t saved;

  if (vr0->type == VR_UNDEFINED)
    {
      set_value_range (vr0, vr1->type, vr1->min, vr1->max, vr1->equiv);
      return;
    }

  if (vr1->type == VR_UNDEFINED)
    {

      return;
    }

  if (vr0->type == VR_VARYING)
    {

      return;
    }

  if (vr1->type == VR_VARYING)
    {
      set_value_range_to_varying (vr0);
      return;
    }

  saved = *vr0;
  union_ranges (&vr0->type, &vr0->min, &vr0->max,
		vr1->type, vr1->min, vr1->max);
  if (vr0->type == VR_VARYING)
    {


      if (((saved.type == VR_RANGE
	    && range_includes_zero_p (saved.min, saved.max) == 0)
	   || (saved.type == VR_ANTI_RANGE
	       && range_includes_zero_p (saved.min, saved.max) == 1))
	  && ((vr1->type == VR_RANGE
	       && range_includes_zero_p (vr1->min, vr1->max) == 0)
	      || (vr1->type == VR_ANTI_RANGE
		  && range_includes_zero_p (vr1->min, vr1->max) == 1)))
	{
	  set_value_range_to_nonnull (vr0, TREE_TYPE (saved.min));


	  if (vr0->equiv)
	    bitmap_clear (vr0->equiv);
	  return;
	}

      set_value_range_to_varying (vr0);
      return;
    }
  set_and_canonicalize_value_range (vr0, vr0->type, vr0->min, vr0->max,
				    vr0->equiv);
  if (vr0->type == VR_VARYING)
    return;


  if (vr0->equiv && vr1->equiv && vr0->equiv != vr1->equiv)
    bitmap_and_into (vr0->equiv, vr1->equiv);
  else if (vr0->equiv && !vr1->equiv)
    bitmap_clear (vr0->equiv);
}
