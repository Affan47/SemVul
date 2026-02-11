insert_suffix(int item_no)
{
    int i,
        j,
        rule_no,
        num_elements = 0;

    unsigned long hash_address = 0;

    rule_no = item_table[item_no].rule_number;
    for (i = rules[rule_no].rhs + item_table[item_no].dot;
         i < rules[rule_no + 1].rhs;
         i++)
    {
        if (rhs_sym[i] IS_A_NON_TERMINAL)
        {
            if (! null_nt[rhs_sym[i]])
            {
                hash_address += rhs_sym[i];
                num_elements++;
            }
        }
        else if (rhs_sym[i] != error_image)
        {
            hash_address += rhs_sym[i];
            num_elements++;
        }
    }

    i = hash_address % SCOPE_SIZE;

    for (j = scope_table[i]; j != NIL; j = scope_element[j].link)
    {
        if (is_suffix_equal(scope_element[j].item, item_no))
            return(scope_element[j].index);
    }
    scope_top++;
    scope_element[scope_top].item = item_no;
    scope_element[scope_top].index = scope_rhs_size + 1;
    scope_element[scope_top].link = scope_table[i];
    scope_table[i] = scope_top;

    scope_rhs_size += (num_elements + 1);

    return(scope_element[scope_top].index);
}
