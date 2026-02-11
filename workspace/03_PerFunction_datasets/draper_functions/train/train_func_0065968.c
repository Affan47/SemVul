setValue(const float * vec4)
    {
        if(vec4) memcpy(getImpl()->value_, vec4, 4*sizeof(float));
    }
