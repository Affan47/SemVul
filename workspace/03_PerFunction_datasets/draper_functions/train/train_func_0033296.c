InverseTransform(const R3Affine& affine)
{

    matrix = matrix * affine.InverseMatrix();
    if (affine.HasMirror()) Mirror();
    InvalidateInverse();
}
