xsh_polynomial_delete_const(const polynomial **p)
{
    if (*p == NULL) return;
    cpl_polynomial_delete((*p)->pol);
    cpl_vector_delete((*p)->vec);
    cpl_free((*p)->shift);
    cpl_free((*p)->scale);
    xsh_free(*p);
    *p = NULL;
    return;
}
