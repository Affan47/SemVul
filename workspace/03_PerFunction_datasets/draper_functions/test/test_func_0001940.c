sge_path_state_dprintf(sge_path_state_class_t *thiz)
{
   sge_path_state_t *ps = (sge_path_state_t *) thiz->sge_path_state_handle;

   DENTER(TOP_LAYER, "sge_path_state_dprintf");

   DPRINTF(("sge_root            >%s<\n", ps->sge_root));
   DPRINTF(("cell_root           >%s<\n", ps->cell_root));
   DPRINTF(("conf_file           >%s<\n", ps->bootstrap_file));
   DPRINTF(("bootstrap_file      >%s<\n", ps->conf_file));
   DPRINTF(("act_qmaster_file    >%s<\n", ps->act_qmaster_file));
   DPRINTF(("acct_file           >%s<\n", ps->acct_file));
   DPRINTF(("reporting_file      >%s<\n", ps->reporting_file));
   DPRINTF(("local_conf_dir      >%s<\n", ps->local_conf_dir));
   DPRINTF(("shadow_masters_file >%s<\n", ps->shadow_masters_file));
   DPRINTF(("alias_file          >%s<\n", ps->alias_file));

   DEXIT;
}
