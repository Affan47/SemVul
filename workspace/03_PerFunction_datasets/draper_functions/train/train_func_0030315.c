getColour() const{
    if(selected) return vec3(1.0f);

    float lc = elapsed - last_action;

    if(lc<1.0f) {
        return touch_colour * (1.0f-lc) + file_colour * lc;
    }

    return file_colour;
}
