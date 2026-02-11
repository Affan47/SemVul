setDestY(float dest_y) {
    if(dest_y == this->dest_y) return;

    this->dest_y = dest_y;

    src_y = pos_y;
    move_elapsed = 0.0f;
}
