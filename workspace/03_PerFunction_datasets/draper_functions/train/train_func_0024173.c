nearest_triangle(triangle *t, triangles *list)
{
    triangle **pattern = list->t;
    int        n       = list->n;
    triangle  *nearest;

    double     dist, mindist;
    int        i;


    mindist = distance_of_triangles(t, pattern[0], NULL);
    nearest = pattern[0];
    for (i = 1; i < n; i++) {
        dist = distance_of_triangles(t, pattern[i], NULL);
        if (mindist > dist) {
            mindist = dist;
            nearest = pattern[i];
        }
    }

    return nearest;
}
