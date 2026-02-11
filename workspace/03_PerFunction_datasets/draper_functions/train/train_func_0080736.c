cb_Properties ()
{
	Edge *e;
	Graph *g = *gg;
	Vertex *v;

	v = g->v_selected_head;
	e = g->e_selected_head;

	if (v && !e) {


		wxString str = wxGetTextFromUser (_("Label:"),
					_("Vertex Properties"),
					v->label, gui);
		if (str.IsEmpty ())
			return;


		while (1) {
			Vertex *f = g->find (str);
			if (!f || (f == v))
				break;
			str += wxT("-dup");
		}

		if (str != v->label) {
			gui->undoableAction (_("Rename vertex"));
			g->rename (v, str);
			redraw ();
		}
	} else if (e) {

		ParamDialogEdge dlg (gui, _("Edge Properties"), e);
		if (dlg.ShowModal () == wxID_CANCEL)
			return;

		int curr_dir = e->directed ? 1 : 0;
		int new_wt = dlg.GetWeight (), new_dir = dlg.GetDirection ();
		int new_flow = dlg.GetFlow ();
		if ((new_wt == e->weight) && (new_dir == curr_dir)) {
			if (e->flow != new_flow) {
				e->flow = new_flow;
				redraw ();
			}
			return;
		}
		if (new_wt == e->weight)
			gui->undoableAction (_("Change edge direction"));
		else if (new_dir == curr_dir)
			gui->undoableAction (_("Change edge weight"));
		else
			gui->undoableAction (_("Change edge weight and direction"));
		e->weight = new_wt;
		if (new_dir == 0)
			e->directed = false;
		else if (new_dir == 1)
			e->directed = true;
		else {
			e->directed = true;
			Vertex *tmp = e->v;
			e->v = e->w;
			e->w = tmp;
		}
		redraw ();
	}
}
