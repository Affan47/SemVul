sh_algo_from_name (xlator_t *this, char *name)
{
        int i = 0;

        if (name == NULL)
                goto out;

        while (afr_self_heal_algorithms[i].name) {
                if (!strcmp (name, afr_self_heal_algorithms[i].name)) {
                        return &afr_self_heal_algorithms[i];
                }

                i++;
        }

out:
        return NULL;
}
