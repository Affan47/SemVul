dht_rename_hashed_dir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                           int32_t op_ret, int32_t op_errno, struct iatt *stbuf,
                           struct iatt *preoldparent,
                           struct iatt *postoldparent,
                           struct iatt *prenewparent,
                           struct iatt *postnewparent, dict_t *xdata)
{
        dht_conf_t   *conf = NULL;
        dht_local_t  *local = NULL;
        int           call_cnt = 0;
        call_frame_t *prev = NULL;
        int           i = 0;

        conf = this->private;
        local = frame->local;
        prev = cookie;

        if (op_ret == -1) {


                gf_log (this->name, GF_LOG_INFO,
                        "rename %s -> %s on %s failed (%s)",
                        local->loc.path, local->loc2.path,
                        prev->this->name, strerror (op_errno));

                local->op_ret   = op_ret;
                local->op_errno = op_errno;
                goto unwind;
        }


        dht_iatt_merge (this, &local->stbuf, stbuf, prev->this);
        dht_iatt_merge (this, &local->preoldparent, preoldparent,
                        prev->this);
        dht_iatt_merge (this, &local->postoldparent, postoldparent,
                        prev->this);
        dht_iatt_merge (this, &local->preparent, prenewparent,
                        prev->this);
        dht_iatt_merge (this, &local->postparent, postnewparent,
                        prev->this);

        call_cnt = local->call_cnt = conf->subvolume_cnt - 1;

        if (!local->call_cnt)
                goto unwind;

        for (i = 0; i < conf->subvolume_cnt; i++) {
                if (conf->subvolumes[i] == local->dst_hashed)
                        continue;
                STACK_WIND (frame, dht_rename_dir_cbk,
                            conf->subvolumes[i],
                            conf->subvolumes[i]->fops->rename,
                            &local->loc, &local->loc2, NULL);
                if (!--call_cnt)
                        break;
        }


        return 0;
unwind:
        WIPE (&local->preoldparent);
        WIPE (&local->postoldparent);
        WIPE (&local->preparent);
        WIPE (&local->postparent);

        DHT_STRIP_PHASE1_FLAGS (&local->stbuf);
        DHT_STACK_UNWIND (rename, frame, local->op_ret, local->op_errno,
                          &local->stbuf, &local->preoldparent,
                          &local->postoldparent,
                          &local->preparent, &local->postparent, NULL);

        return 0;
}
