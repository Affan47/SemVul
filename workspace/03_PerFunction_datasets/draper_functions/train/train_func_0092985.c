copyValue(const vec2* value) {
    for(size_t i=0; i<length; i++) {
        this->value[i] = value[i];
    }
}
