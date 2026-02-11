type_as_cvff(struct model_pak *model)
{
gint nb, nc;
GSList *clist, *mlist;
struct core_pak *core;
struct mol_pak *mol;

g_assert(model != NULL);


type_clear(model);


for (mlist=model->moles ; mlist ; mlist=g_slist_next(mlist))
  {
  mol = mlist->data;
  nc = g_slist_length(mol->cores);


  for (clist=mol->cores ; clist ; clist=g_slist_next(clist))
    {
    core = clist->data;
    nb = g_slist_length(core->bonds);


    if (core->atom_type)
      continue;

    switch(core->atom_code)
      {

      case 1:
        if (type_core_has_bond(8, core))
          {

          if (nc == 3)
            core->atom_type = g_strdup("h*");
          else
            core->atom_type = g_strdup("ho");
          }
        else
          core->atom_type = g_strdup("h");
        break;


      case 6:
        switch(nb)
          {
          case 4:
            core->atom_type = g_strdup("cg");
            break;

          case 3:


            if (type_core_has_bond(8, core) == 2)
              core->atom_type = g_strdup("c-");
            else
              core->atom_type = g_strdup("cp");
            break;

          case 2:

            core->atom_type = g_strdup("c");
            break;

          case 1:

            core->atom_type = g_strdup("ct");
            break;

          default:
            core->atom_type = g_strdup("c");
          }
        break;


      case 8:


        switch (nb)
          {
          case 2:
            if (type_core_has_bond(1, core) == 2)
              core->atom_type = g_strdup("o*");
            else
              {
              if (type_core_has_bond(1, core) == 1)
                core->atom_type = g_strdup("oh");
              else
                core->atom_type = g_strdup("o");
              }
            break;

          case 1:
            if (type_core_has_bond(1, core))
              core->atom_type = g_strdup("oh");
            else
              core->atom_type = g_strdup("o");
            break;

          default:
            core->atom_type = g_strdup("o");
            break;
          }
        break;

      default:

        core->atom_type = g_strdup_printf("%s", elements[core->atom_code].symbol);
        break;
      }
    }
  }
}
