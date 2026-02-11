GC_register_disappearing_link(GC_PTR * link)
# else
    int GC_register_disappearing_link(link)
    GC_PTR * link;
# endif
{
    ptr_t base;

    base = (ptr_t)GC_base((GC_PTR)link);
    if (base == 0)
    	ABORT("Bad arg to GC_register_disappearing_link");
    return(GC_general_register_disappearing_link(link, base));
}
