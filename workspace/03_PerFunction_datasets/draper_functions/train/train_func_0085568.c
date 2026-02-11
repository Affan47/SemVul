multiattrib_action_promote_attribute (GSCHEM_TOPLEVEL *w_current,
                                                  OBJECT *object,
                                                  OBJECT *o_attrib)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  OBJECT *o_new;

  if (o_is_visible (toplevel, o_attrib)) {

    (void) o_attrib_add_attrib (w_current,
				o_text_get_string (w_current->toplevel, o_attrib),
				VISIBLE,
				o_attrib->show_name_value,
				object);
  } else {

      o_new = o_object_copy (toplevel, o_attrib);
      s_page_append (toplevel, toplevel->page_current, o_new);

      o_attrib_attach (toplevel, o_new, object, TRUE);


      g_run_hook_object (w_current, "%add-objects-hook", o_new);
  }
  w_current->toplevel->page_current->CHANGED = 1;
  o_undo_savestate (w_current, UNDO_ALL);
}
