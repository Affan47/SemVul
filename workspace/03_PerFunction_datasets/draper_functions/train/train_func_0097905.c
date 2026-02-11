bcf1_sync_info(bcf1_t *line, kstring_t *str)
{

    int i, irm = -1;
    for (i=0; i<line->n_info; i++)
    {
        bcf_info_t *info = &line->d.info[i];
        if ( !info->vptr )
        {

            if ( irm < 0 ) irm = i;
            continue;
        }
        kputsn_(info->vptr - info->vptr_off, info->vptr_len + info->vptr_off, str);
        if ( irm >=0 )
        {
            bcf_info_t tmp = line->d.info[irm]; line->d.info[irm] = line->d.info[i]; line->d.info[i] = tmp;
            while ( irm<=i && line->d.info[irm].vptr ) irm++;
        }
    }
    if ( irm>=0 ) line->n_info = irm;
}
