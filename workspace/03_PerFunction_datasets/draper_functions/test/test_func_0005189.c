setLightAmbient(GLfloat r, GLfloat g, GLfloat b)
    {
        if((mLightAmbient[0] != r) ||
           (mLightAmbient[1] != g) ||
           (mLightAmbient[2] != b))
        {
            mLightAmbient[0] = r;
            mLightAmbient[1] = g;
            mLightAmbient[2] = b;

            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &mLightAmbient[0]);
        }
    }
