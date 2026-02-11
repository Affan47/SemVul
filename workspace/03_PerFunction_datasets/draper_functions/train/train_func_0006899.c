cos_dict_find(const cos_dict_t *pcd, const byte *key_data, uint key_size)
{
    cos_dict_element_t *pcde = pcd->elements;

    for (; pcde; pcde = pcde->next)
        if (!bytes_compare(key_data, key_size, pcde->key.data, pcde->key.size))
            return &pcde->value;
    return 0;
}
