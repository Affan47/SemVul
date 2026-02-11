_dxfEigenVector(int start_vector, int end_vector)
{
    float *v;


    v=(float *)DXAllocate((unsigned) (end_vector-start_vector+1)*sizeof(float));
    if (!v)
	return NULL;
    return v-start_vector;
}
