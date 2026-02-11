slider_look(DimensionName d, Adjustable* a) const {
    const OLKitImpl& i = *impl_;
    const OL_Specs* s = i.specs_;
    OL_Dragbox* b = new OL_Dragbox(this, s, d);
    OL_Channel* c = new OL_Channel(this, s, a, d, b);
    return new OL_Slider(s, a, i.style_, d, c, b);
}
