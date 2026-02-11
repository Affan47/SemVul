Update () {
    register Perspective* p = shown;
    int h, oldwidth, oldheight;
    float aspect;
    Scene* s;
    Shape ns;

    oldwidth = p->width;
    oldheight = p->height;
    *p = *view;
    aspect = float(p->height) / float(p->width);

    SizeKnob();
    if (p->width != oldwidth || p->height != oldheight) {
	h = Math::round(aspect * float(shape->width));
#if 0
	printf("pw=%d, ph=%d, ow=%d, oh=%d, sw=%d, sh=%d, aspect=%f, h=%d\n",
		p->width, p->height, oldwidth, oldheight, shape->width, shape->height, aspect, h);
#endif
	if (h == shape->height || h+1 == shape->height || h-1==shape->height) {
	    Draw();
	} else {
	    shape->height = h;
	    if ((s = Parent()) != nil) {
		s->Change(this);
	    }
	}
    } else if (
	prevl != left || prevb != bottom || prevr != right || prevt != top
    ) {
	Draw();
    }
}
