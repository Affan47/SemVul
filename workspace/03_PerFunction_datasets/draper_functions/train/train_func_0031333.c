front_buffer() {
    CanvasRep& c = *rep();
    if (c.copybuffer_ != CanvasRep::unbound) {
	c.drawbuffer_ = c.copybuffer_;
    }
}
