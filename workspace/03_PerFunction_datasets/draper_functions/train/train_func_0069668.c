vgauge(Adjustable* a) const {
    Patch* patch = new Patch(nil);
    patch->body(new OL_Gauge(this, impl_->specs_, Dimension_Y, a, patch));
    return patch;
}
