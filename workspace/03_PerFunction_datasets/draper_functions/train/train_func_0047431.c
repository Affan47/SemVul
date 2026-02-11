afr_sh_entry_erase_pending (call_frame_t *frame, xlator_t *this)
{
        afr_local_t     *local = NULL;
        afr_self_heal_t *sh = NULL;
        afr_private_t   *priv = NULL;
        int              call_count = 0;
        int              i = 0;
        dict_t          **erase_xattr = NULL;
        int              need_unwind = 0;

        local = frame->local;
        sh = &local->self_heal;
        priv = this->private;

        if (sh->entries_skipped) {
                need_unwind = 1;
                sh->op_failed = _gf_true;
                goto out;
        }
        afr_sh_pending_to_delta (priv, sh->xattr, sh->delta_matrix, sh->success,
                                 priv->child_count, AFR_ENTRY_TRANSACTION);

        erase_xattr = GF_CALLOC (sizeof (*erase_xattr), priv->child_count,
                                 gf_afr_mt_dict_t);

        for (i = 0; i < priv->child_count; i++) {
                if (sh->xattr[i]) {
                        call_count++;

                        erase_xattr[i] = get_new_dict();
                        dict_ref (erase_xattr[i]);
                }
        }

        if (call_count == 0)
                need_unwind = 1;

        afr_sh_delta_to_xattr (priv, sh->delta_matrix, erase_xattr,
                               priv->child_count, AFR_ENTRY_TRANSACTION);

        local->call_count = call_count;
        for (i = 0; i < priv->child_count; i++) {
                if (!erase_xattr[i])
                        continue;

                gf_log (this->name, GF_LOG_TRACE,
                        "erasing pending flags from %s on %s",
                        local->loc.path, priv->children[i]->name);

                STACK_WIND_COOKIE (frame, afr_sh_entry_erase_pending_cbk,
                                   (void *) (long) i,
                                   priv->children[i],
                                   priv->children[i]->fops->xattrop,
                                   &local->loc,
                                   GF_XATTROP_ADD_ARRAY, erase_xattr[i]);
                if (!--call_count)
                        break;
        }

        for (i = 0; i < priv->child_count; i++) {
                if (erase_xattr[i]) {
                        dict_unref (erase_xattr[i]);
                }
        }
        GF_FREE (erase_xattr);

out:
        if (need_unwind)
                afr_sh_entry_finish (frame, this);

        return 0;
}
