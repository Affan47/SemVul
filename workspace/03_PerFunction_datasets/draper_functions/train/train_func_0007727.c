exprs_to_byte_exprs(struct atom *atom)
{
    if(atom->type != ATOM_TYPE_EXPRS)
    {
        LOG(LOG_ERROR, ("can't convert atom of type %d to byte exprs.\n",
                        atom->type));
        exit(1);
    }
    atom->type = ATOM_TYPE_BYTE_EXPRS;

    pc_add(vec_count(atom->u.exprs));
    return atom;
}
