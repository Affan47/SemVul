client_statfs (call_frame_t *frame, xlator_t *this, loc_t *loc, dict_t *xdata)
{
        int          ret  = -1;
        clnt_conf_t *conf = NULL;
        rpc_clnt_procedure_t *proc = NULL;
        clnt_args_t  args = {0,};

        conf = this->private;
        if (!conf || !conf->fops)
                goto out;

        args.loc = loc;
        args.xdata = xdata;

        proc = &conf->fops->proctable[GF_FOP_STATFS];
        if (!proc) {
                gf_log (this->name, GF_LOG_ERROR,
                        "rpc procedure not found for %s",
                        gf_fop_list[GF_FOP_STATFS]);
                goto out;
        }
        if (proc->fn)
                ret = proc->fn (frame, this, &args);
out:
        if (ret)
                STACK_UNWIND_STRICT (statfs, frame, -1, ENOTCONN, NULL, NULL);

	return 0;
}
