CVAdjustSpline(CharView *cv) {
    Spline *old = cv->p.spline;
    TPoint tp[5];
    real t;
    Spline1D *oldx = &old->splines[0], *oldy = &old->splines[1];

    if ( cv->b.layerheads[cv->b.drawmode]->order2 )
return;

    tp[0].x = cv->info.x; tp[0].y = cv->info.y; tp[0].t = cv->p.t;
    t = cv->p.t/10;
    tp[1].x = ((oldx->a*t+oldx->b)*t+oldx->c)*t + oldx->d;
    tp[1].y = ((oldy->a*t+oldy->b)*t+oldy->c)*t + oldy->d;
    tp[1].t = t;
    t = 1-(1-cv->p.t)/10;
    tp[2].x = ((oldx->a*t+oldx->b)*t+oldx->c)*t + oldx->d;
    tp[2].y = ((oldy->a*t+oldy->b)*t+oldy->c)*t + oldy->d;
    tp[2].t = t;
    tp[3] = tp[0];
    tp[4] = tp[0];
    cv->p.spline = ApproximateSplineFromPoints(old->from,old->to,tp,5,old->order2);
    old->from->pointtype = pt_corner; old->to->pointtype = pt_corner;
    old->from->nextcpdef = old->to->prevcpdef = false;
    SplineFree(old);
    CVSetCharChanged(cv,true);
}
