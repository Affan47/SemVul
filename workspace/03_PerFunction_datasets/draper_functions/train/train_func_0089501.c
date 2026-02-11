add_IntSet(register IntSet dest, register int total_element,
                                            register unsigned int* element)
{   register int  i;
    register unsigned int  tmp;

    for  (i=0; i<total_element; i++)
    {   tmp = *element++;
#ifdef DEBUG_INTSET
        if  (tmp >= dest[-2])
        {   fputs("IntSet add_IntSet(IntSet, int, unsigned int*)"
                    " : Range Error.\n", stderr);
            exit(1);
        }
#endif
        add1_IntSet(dest, tmp);
    }

    return;
}
