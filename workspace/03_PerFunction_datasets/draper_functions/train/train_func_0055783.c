gamgi_math_matrix_unit_check (double *m)
{
if (m[0] == 1.0 && m[1] == 0.0 && m[2] == 0.0 &&
    m[3] == 0.0 && m[4] == 1.0 && m[5] == 0.0 &&
    m[6] == 0.0 && m[7] == 0.0 && m[8] == 1.0) return TRUE;

return FALSE;
}
