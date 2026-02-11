search_constant_character(const char *__data, int __size)
{   int  i;
    int  j;
    int  k;
    struct ConstantTable* ptr;

    for  (i=0; i<constant_number; i++)
    {   j = offset[i];
        if  (j != -1)
        {   ptr = &constant_table[j];
            if  (ptr->user_allocated == FALSE  &&  ptr->type == TYPE_CHARACTER
             && __data != NULL) {
                for (k=0 ; k<__size && k<strlen(__data) ; k++) {
                    if (ptr->val.c != (int)__data[k])
                        break;
                    ptr++;
                }
                for ( ; k<__size ; k++) {
                    if (ptr->val.c != ' ')
                        break;
                    ptr++;
                }
                if (k==__size)
                {   return  i;
                }
            }
        }
    }
    return  -1;
}
