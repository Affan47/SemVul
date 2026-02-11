OnKeyPress (wxKeyEvent &event)
{
	Graph *g = *gg;

	if (!event.HasModifiers () && (event.GetKeyCode () == WXK_DELETE)) {


		gui->undoableAction (_("Delete objects"));

		Edge *prevE, *e = g->e_selected_head;
		while (e) {
			prevE = e;
			e = e->next;
			g->remove (prevE);
		}

		Vertex *prevV, *v = g->v_selected_head;
		while (v) {
			prevV = v;
			v = v->next;
			g->remove (prevV);
		}

		redraw ();
		return;
	}

	if (event.GetKeyCode () == ' ') {
		gui->toggleMode ();
		return;
	}


	event.Skip ();
}
