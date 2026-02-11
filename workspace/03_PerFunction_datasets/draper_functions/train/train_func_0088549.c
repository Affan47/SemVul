GetOrientation () {
    Transformer* t = GetTransformer();

    return (t == nil || !t->Rotated90()) ? Horizontal : Vertical;
}
