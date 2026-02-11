test_select_hyper_iter1(void *_elem, hid_t UNUSED type_id, unsigned UNUSED ndim, const hsize_t UNUSED *point, void *_operator_data)
{
    uint8_t *tbuf=(uint8_t *)_elem,
            **tbuf2=(uint8_t **)_operator_data;

    if(*tbuf!=**tbuf2)
        return(-1);
    else {
        (*tbuf2)++;
        return(0);
    }
}
