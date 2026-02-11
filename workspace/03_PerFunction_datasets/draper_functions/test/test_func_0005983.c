Reversible () {
    Iterator i;

    for (First(i); !Done(i); Next(i)) {
        if (GetCommand(i)->Reversible()) {
            return true;
        }
    }
    return false;
}
