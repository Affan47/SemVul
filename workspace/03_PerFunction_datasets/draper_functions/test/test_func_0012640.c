gamgi_math_polygon_diameter (gamgi_cell *cell,
gamgi_direction *direction, double *r1, double *r2)
{
gamgi_darray *darray;
double point[3];
double v[3];
double a, b, c, d;
double f1, f2;


darray = gamgi_engine_darray_create (2, 0, 3);


gamgi_math_vector_sub (r2, r1, v);
a = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
b = 2 * (r1[0] * v[0] + r1[1] * v[1] + r1[2] * v[2]);
c = r1[0] * r1[0] + r1[1] * r1[1] + r1[2] * r1[2] - cell->v1 * cell->v1;
d = b * b - 4 * a * c;


if (a < GAMGI_MATH_DIRECTION_LENGTH) return darray;
if (d < GAMGI_MATH_DIRECTION_LENGTH) return darray;

f1 = - b - sqrt (d); f1 /= 2 * a;
f2 = - b + sqrt (d); f2 /= 2 * a;


point[0] = r1[0] + f1 * v[0];
point[1] = r1[1] + f1 * v[1];
point[2] = r1[2] + f1 * v[2];
gamgi_engine_darray_push (darray, point);

point[0] = r1[0] + f2 * v[0];
point[1] = r1[1] + f2 * v[1];
point[2] = r1[2] + f2 * v[2];
gamgi_engine_darray_push (darray, point);

return darray;
}
