_mesa_QueryMatrixxOES(GLfixed mantissa[16], GLint exponent[16])
{
    GLfloat matrix[16];
    GLint tmp;
    GLenum currentMode = GL_FALSE;
    GLenum desiredMatrix = GL_FALSE;


    GLbitfield rv;
    register unsigned int i;
    unsigned int bit;


    static struct {
        GLenum currentMode;
        GLenum desiredMatrix;
    } modes[] = {
        {GL_MODELVIEW, GL_MODELVIEW_MATRIX},
        {GL_PROJECTION, GL_PROJECTION_MATRIX},
        {GL_TEXTURE, GL_TEXTURE_MATRIX},
    };


    _mesa_GetIntegerv(GL_MATRIX_MODE, &tmp);
    currentMode = (GLenum) tmp;


    for (i = 0; i < sizeof(modes)/sizeof(modes[0]); i++) {
        if (modes[i].currentMode == currentMode) {
            desiredMatrix = modes[i].desiredMatrix;
            break;
        }
    }
    if (desiredMatrix == GL_FALSE) {

        return 0xffff;
    }


    _mesa_GetFloatv(desiredMatrix, matrix);

    rv = 0;
    for (i = 0, bit = 1; i < 16; i++, bit<<=1) {
        float normalizedFraction;
        int exp;

        switch (fpclassify(matrix[i])) {


            case FP_SUBNORMAL:
            case FP_NORMAL:
            case FP_ZERO:
                normalizedFraction = (GLfloat)frexp(matrix[i], &exp);
                mantissa[i] = FLOAT_TO_FIXED(normalizedFraction);
                exponent[i] = (GLint) exp;
                break;


            case FP_NAN:
                mantissa[i] = INT_TO_FIXED(0);
                exponent[i] = (GLint) 0;
                rv |= bit;
                break;

            case FP_INFINITE:


                if (matrix[i] > 0) {
                    mantissa[i] = INT_TO_FIXED(1);
                }
                else {
                    mantissa[i] = -INT_TO_FIXED(1);
                }
                exponent[i] = (GLint) 0;
                rv |= bit;
                break;


            default:
                mantissa[i] = INT_TO_FIXED(2);
                exponent[i] = (GLint) 0;
                rv |= bit;
                break;
        }

    }


    return rv;
}
