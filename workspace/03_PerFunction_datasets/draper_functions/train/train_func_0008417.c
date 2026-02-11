totalGSGraphic (Graphic* g, Graphic& gs) {
    Graphic* parent = g->Parent();

    if (parent == nil) {
        concatGraphic(g, nil, g, &gs);

    } else {
        totalGSGraphic(parent, gs);
        concatGraphic(g, g, &gs, &gs);
    }
}
