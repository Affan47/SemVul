GlyphNormalXform(Matrix t, int n,
   Point *normals_old, Point *normals_new)
{
    int i;


    t = DXAdjointTranspose(t);
    for (i = 0; i < n; i++) {
        normals_new[i] = DXApply(normals_old[i], t);

         normals_new[i] = DXNormalize(normals_new[i]);
    }
    return OK;
}
