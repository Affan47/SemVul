apply(unsigned int &width, unsigned int &height,
                                  bool make_fit) const {


    unsigned int w = width - base_width, h = height - base_height;

    if (min_aspect_y > 0 && w * min_aspect_y < min_aspect_x * h) {
        closestPointToAspect(w, h, w, h, min_aspect_x, min_aspect_y);

        w = increaseToMultiple(w, width_inc);
        h = decreaseToMultiple(h, height_inc);
    } else if (max_aspect_x > 0 && w * max_aspect_y > max_aspect_x * h) {
        closestPointToAspect(w, h, w, h, max_aspect_x, max_aspect_y);

        w = decreaseToMultiple(w, width_inc);
        h = increaseToMultiple(h, height_inc);
    }


    if (w + base_width < min_width) {
        w = increaseToMultiple(min_width - base_width, width_inc);

        if (max_aspect_x > 0 && w * max_aspect_y > max_aspect_x * h)
            h = increaseToMultiple(w * max_aspect_y / max_aspect_x, height_inc);
    }

    if (h + base_height < min_height) {
        h = increaseToMultiple(min_height - base_height, height_inc);

        if (min_aspect_y > 0 && w * min_aspect_y < min_aspect_x * h)
            w = increaseToMultiple(h * min_aspect_x / min_aspect_y, width_inc);
    }

    unsigned int max_w = (make_fit && (width < max_width || max_width == 0)) ?  width : max_width;
    unsigned int max_h = (make_fit && (height < max_height || max_height == 0)) ?  height : max_height;


    if (max_w > 0 && w + base_width > max_w)
        w = max_w - base_width;

    if (max_h > 0 && h + base_height > max_h)
        h = max_h - base_height;

    w = decreaseToMultiple(w, width_inc);
    h = decreaseToMultiple(h, height_inc);


    if (min_aspect_y > 0 && w * min_aspect_y < min_aspect_x * h)
        h = decreaseToMultiple(w * min_aspect_y / min_aspect_x, height_inc);

    if (max_aspect_x > 0 && w * max_aspect_y > max_aspect_x * h)
        w = decreaseToMultiple(h * max_aspect_x / max_aspect_y, width_inc);

    width = w + base_width;
    height = h + base_height;
}
