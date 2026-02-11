Grasp (Event& e) {
    Iterator i;

    for (First(i); !Done(i); Next(i)) {
	GetManip(i)->Grasp(e);
        ManipList* ml = (ManipList*) Elem(i);
        ml->manipulating(true);
    }
}
