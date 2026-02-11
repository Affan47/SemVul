fl_tablep(value_t *args, uint32_t nargs)
{
    argcount("table?", nargs, 1);
    return ishashtable(args[0]) ? FL_T : FL_F;
}
