split(void)
{
    string_ty       **new_hash_table;
    str_hash_ty     new_hash_modulus;
    str_hash_ty     new_hash_mask;
    str_hash_ty     idx;


    assert(is_power_of_two(hash_modulus));
    new_hash_modulus = hash_modulus * 2;
    new_hash_mask = new_hash_modulus - 1;
    new_hash_table = mem_alloc(new_hash_modulus * sizeof(string_ty *));


    for (idx = 0; idx < hash_modulus; ++idx)
    {
        string_ty       *p;

        new_hash_table[idx] = 0;
        new_hash_table[idx + hash_modulus] = 0;
        p = hash_table[idx];
        while (p)
        {
            string_ty       *p2;
            str_hash_ty     new_idx;

            p2 = p;
            p = p->str_next;

            assert((p2->str_hash & hash_mask) == idx);
            new_idx = p2->str_hash & new_hash_mask;
            p2->str_next = new_hash_table[new_idx];
            new_hash_table[new_idx] = p2;
        }
    }
    mem_free(hash_table);
    hash_table = new_hash_table;
    hash_modulus = new_hash_modulus;
    hash_mask = new_hash_mask;
}
