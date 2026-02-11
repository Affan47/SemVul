client_finodelk (call_frame_t *frame, xlator_t *this, const char *volume,
                 fd_t *fd, int32_t cmd, struct gf_flock *lock, dict_t *xdata)
{
        int          ret  = -1;
        clnt_conf_t *conf = NULL;
        rpc_clnt_procedure_t *proc = NULL;
        clnt_args_t  args = {0,};

        conf = this->private;
        if (!conf || !conf->fops)
                goto out;

        args.fd     = fd;
        args.cmd    = cmd;
        args.flock  = lock;
        args.volume = volume;
        args.xdata = xdata;

        proc = &conf->fops->proctable[GF_FOP_FINODELK];
        if (!proc) {
                gf_log (this->name, GF_LOG_ERROR,
                        "rpc procedure not found for %s",
                        gf_fop_list[GF_FOP_FINODELK]);
                goto out;
        }
        if (proc->fn)
                ret = proc->fn (frame, this, &args);
out:
        if (ret)
                STACK_UNWIND_STRICT (finodelk, frame, -1, ENOTCONN, NULL);

	return 0;
}
