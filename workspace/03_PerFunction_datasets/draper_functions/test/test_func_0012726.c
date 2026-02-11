image_resize(unsigned char *rgb, int ox, int oy, int nx, int ny)
{

    const int components = 3;
    unsigned char *new;

    double ux, uy;
    double dx, dy;

    int i, j, k;

    new = malloc(nx * ny * components);

    if (new == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    dx = (double)ox / nx;
    dy = (double)oy / ny;

    uy = 0.0;

    for (j = 0; j < ny; j++) {

        ux = 0.0;

        for (i = 0; i < nx; i++) {

            for (k = 0; k < components; k++)

                new[(j * nx + i) * components + k] = image_resample(rgb, ux, uy, dx, dy, ox, oy, k);

            ux += dx;
        }

        uy += dy;
    }

    return (new);
}
