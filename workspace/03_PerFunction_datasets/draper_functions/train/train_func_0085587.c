FcVStackPushMatrix (FcConfigParse *parse, FcMatrix *matrix)
{
    FcVStack    *vstack;
    matrix = FcMatrixCopy (matrix);
    if (!matrix)
	return FcFalse;
    vstack = FcVStackCreateAndPush (parse);
    if (!vstack)
	return FcFalse;
    vstack->u.matrix = matrix;
    vstack->tag = FcVStackMatrix;
    return FcTrue;
}
