FullRedraw() {
    EView *V = View;
    EEditPort *W;
    int Min, Max;

    while (V) {
        W = GetViewVPort(V);


        Min = VToR(W->TP.Row);
        Max = W->TP.Row + W->Rows;
        if (Max >= VCount)
            Max = RCount;
        else
            Max = VToR(Max);
        Draw(Min, Max);
        V = V->Next;
        if (V == View)
            break;
    }
}
