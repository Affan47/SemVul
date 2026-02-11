write_types_process_field (type_p f, const struct walk_type_data *d)
{
  const struct write_types_data *wtd;
  const char *cast = d->needs_cast_p ? "(void *)" : "";
  wtd = (const struct write_types_data *) d->cookie;

  switch (f->kind)
    {
    case TYPE_POINTER:
      oprintf (d->of, "%*s%s (%s%s", d->indent, "",
	       wtd->subfield_marker_routine, cast, d->val);
      if (wtd->param_prefix)
	{
	  oprintf (d->of, ", %s", d->prev_val[3]);
	  if (d->orig_s)
	    {
	      oprintf (d->of, ", gt_%s_", wtd->param_prefix);
	      output_mangled_typename (d->of, d->orig_s);
	    }
	  else
	    oprintf (d->of, ", gt_%sa_%s", wtd->param_prefix, d->prev_val[0]);
	}
      oprintf (d->of, ");\n");
      if (d->reorder_fn && wtd->reorder_note_routine)
	oprintf (d->of, "%*s%s (%s%s, %s, %s);\n", d->indent, "",
		 wtd->reorder_note_routine, cast, d->val,
		 d->prev_val[3], d->reorder_fn);
      break;

    case TYPE_STRING:
      if (wtd->param_prefix == NULL)
	break;

    case TYPE_STRUCT:
    case TYPE_UNION:
    case TYPE_LANG_STRUCT:
    case TYPE_PARAM_STRUCT:
      oprintf (d->of, "%*sgt_%s_", d->indent, "", wtd->prefix);
      output_mangled_typename (d->of, f);
      oprintf (d->of, " (%s%s);\n", cast, d->val);
      if (d->reorder_fn && wtd->reorder_note_routine)
	oprintf (d->of, "%*s%s (%s%s, %s%s, %s);\n", d->indent, "",
		 wtd->reorder_note_routine, cast, d->val, cast, d->val,
		 d->reorder_fn);
      break;

    case TYPE_SCALAR:
      break;

    default:
      abort ();
    }
}
