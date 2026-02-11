LimitMagnification (float desired) {
    const float lo = 1./8.;
    const float hi = 16.;

    return (desired < lo) ? lo : (desired > hi) ? hi : desired;
}
