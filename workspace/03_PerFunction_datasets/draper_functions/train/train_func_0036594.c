vector_fast_square_root (const float* x_input, float* y_output, int N)
{
    int i;
    float x;
    FAST_SQUARE_ROOT_PREFACE;

    for (i=0; i<N; ++i)
    {
	x = x_input[i];
	FAST_SQUARE_ROOT_BODY
	y_output[i] = ans;
    }
}
