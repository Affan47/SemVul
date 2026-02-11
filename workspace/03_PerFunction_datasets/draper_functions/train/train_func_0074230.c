intersects (BoxObj& userb, Graphic* gs) {
    return
        (!gs->GetPattern()->None() && f_intersects(userb, gs)) ||
        s_intersects(userb, gs);
}
