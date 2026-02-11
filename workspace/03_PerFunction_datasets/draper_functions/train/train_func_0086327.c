Init (Selection* s) {
    Iterator i;

    Clear();
    for (s->First(i); !s->Done(i); s->Next(i)) {
        Append(s->GetView(i)->GetGraphicComp());
    }
}
