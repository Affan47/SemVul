Resize () {
    int w = xmax + 1;
    if (shape->width != w) {
	Shape ns = *shape;
	ns.width = w;
	Reshape(ns);
    }
    SizeKnob();
}
