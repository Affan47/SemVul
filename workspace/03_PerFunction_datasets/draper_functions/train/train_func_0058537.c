draw (wxDC &dc, Vertex *v)
{
	int r = Canvas::vertex_radius;
	wxColour col = black;

	if (v->selected) {
		unsigned int idx = v->selection_colour %
						selection_colours.size ();
		col = selection_colours[idx];
	}

	dc.SetBrush (wxBrush (col));
	dc.SetPen (wxPen (col));

	dc.DrawCircle (v->x, v->y, r);

	if (do_labels) {
		dc.SetFont (*bold_font);
		dc.SetTextForeground (col);
		dc.DrawText (v->label, v->x + r, v->y - 2 * r);
	}
}
