DeepCopy () {
    Clipboard* cbnew = new Clipboard;
    Iterator i;

    for (First(i); !Done(i); Next(i)) {
        cbnew->Append((GraphicComp*) GetComp(i)->Copy());
    }
    return cbnew;
}
