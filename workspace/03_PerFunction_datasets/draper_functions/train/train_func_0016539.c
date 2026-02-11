cofactor() const {
	Matrix4 out;


    int i = 1;

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {

            float det = subDeterminant(r, c);
            out.elt[r][c] = i * det;
            i = -i;
        }
        i = -i;
    }

    return out;
}
