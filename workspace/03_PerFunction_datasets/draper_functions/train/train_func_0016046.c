search_constant_complex(real __re, real __im)
{   int  i;
    int  j;
    struct ConstantTable* ptr;

    for  (i=0; i<constant_number; i++)
    {   j = offset[i];
        if  (j != -1)
        {   ptr = &constant_table[j];
            if  (ptr->user_allocated == FALSE  &&  ptr->type == TYPE_COMPLEX
                 && ptr->val.r == __re)
            {   if  ((ptr+1)->val.r == __im)
                {   return  i;
                }
            }
            else if  (ptr->user_allocated == FALSE
                      &&  ptr->type == TYPE_DCOMPLEX
                      && ptr->val.d == __re)
            {   if  ((ptr+1)->val.d == __im)
                {   return  i;
                }
            }
        }
    }
    return  -1;
}
