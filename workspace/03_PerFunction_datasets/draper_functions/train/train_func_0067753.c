trash_rename (call_frame_t *frame, xlator_t *this, loc_t *oldloc,
              loc_t *newloc)
{
        trash_elim_pattern_t  *trav  = NULL;
        trash_private_t *priv = NULL;
        trash_local_t   *local = NULL;
        struct tm       *tm = NULL;
        char             timestr[256] = {0,};
        time_t           utime = 0;
        int32_t          match = 0;

        priv = this->private;
        if (priv->eliminate) {
                trav = priv->eliminate;
                while (trav) {
                        if (fnmatch(trav->pattern, newloc->name, 0) == 0) {
                                match++;
                                break;
                        }
                        trav = trav->next;
                }
        }

        if ((strncmp (oldloc->path, priv->trash_dir,
                      strlen (priv->trash_dir)) == 0) || match) {


                STACK_WIND (frame, trash_common_rename_cbk,
                            this->children->xlator,
                            this->children->xlator->fops->rename,
                            oldloc, newloc);

                return 0;
        }

        local = GF_CALLOC (1, sizeof (trash_local_t),
                           gf_trash_mt_trash_local_t);
        if (!local) {
                gf_log (this->name, GF_LOG_ERROR, "out of memory");
                TRASH_STACK_UNWIND (rename, frame, -1, ENOMEM,
                                    NULL, NULL, NULL, NULL, NULL);
                return 0;
        }

        frame->local = local;
        loc_copy (&local->loc, oldloc);

        loc_copy (&local->newloc, newloc);

        strcpy (local->origpath, newloc->path);
        strcpy (local->newpath, priv->trash_dir);
        strcat (local->newpath, newloc->path);

        {


                utime = time (NULL);
                tm    = localtime (&utime);
                strftime (timestr, 256, ".%Y-%m-%d-%H%M%S", tm);
                strcat (local->newpath, timestr);
        }


        STACK_WIND (frame, trash_rename_lookup_cbk,
                    this->children->xlator,
                    this->children->xlator->fops->lookup, newloc, 0);

        return 0;
}
