operator*(const float s) const {
    Matrix4 result;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            result.elt[r][c] = elt[r][c] * s;
        }
    }

    return result;
}
