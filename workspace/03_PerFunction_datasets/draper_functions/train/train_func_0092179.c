vector_reuse(struct vector *vector)
{
    if (vector == NULL)
        return vector_new();
    else {
        vector_clear(vector);
        return vector;
    }
}
