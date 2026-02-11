counting_closure(vm the_vm, const char *status, void *data)
{
    struct qcl_data *qdata = data;

    if (qdata->show_all || qdata->progr == progr_of_cur_verb(the_vm))
	qdata->i++;

    return TEA_CONTINUE;
}
