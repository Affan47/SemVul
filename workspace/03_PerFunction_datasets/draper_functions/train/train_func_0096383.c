marker_xtime_update_marks (xlator_t *this, marker_local_t *local)
{
        GF_VALIDATE_OR_GOTO ("marker", this, out);
        GF_VALIDATE_OR_GOTO (this->name, local, out);

        if ((local->pid == GF_CLIENT_PID_GSYNCD) ||
            (local->pid == GF_CLIENT_PID_DEFRAG))
                goto out;

        marker_gettimeofday (local);

        marker_local_ref (local);

        marker_create_frame (this, local);
out:
        return 0;
}
