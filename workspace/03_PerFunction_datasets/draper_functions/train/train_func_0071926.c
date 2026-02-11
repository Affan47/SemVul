Resize() {
    register TrayElement* e;

    canvas->SetBackground(output->GetBgColor());
    if (bg != nil) {
	Place(bg, 0, 0, xmax, ymax);
    }

    for (e = head; e != nil; e = e->next) {
	tsolver->SetShape(e->child);
    }

    tsolver->Solve(xmax+1, ymax+1);

    for (e = head; e != nil; e = e->next) {
	PlaceElement(e);
    }
}
