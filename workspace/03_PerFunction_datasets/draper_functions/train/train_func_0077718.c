cos_array_reorder(const cos_array_t *pca, cos_array_element_t *first)
{
    cos_array_element_t *last;
    cos_array_element_t *next;
    cos_array_element_t *pcae;

    for (pcae = (first ? first : pca->elements), last = NULL; pcae;
         pcae = next)
        next = pcae->next, pcae->next = last, last = pcae;
    return last;
}
