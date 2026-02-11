arg_finit(arg_list * pal)
{
    while (pal->depth) {
        arg_source *pas = &pal->sources[--(pal->depth)];

        if (pas->is_file)
            fclose(pas->u.file);
        else if (pas->u.s.memory)
            gs_free_object(pas->u.s.memory, pas->u.s.chars, "arg_finit");
    }
}
