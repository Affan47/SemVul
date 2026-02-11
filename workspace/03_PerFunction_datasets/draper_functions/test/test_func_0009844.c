setValue(float value) {
    if(baked && this->value == value) return;

    this->value = value;
    modified = true;
    initialized = true;
}
