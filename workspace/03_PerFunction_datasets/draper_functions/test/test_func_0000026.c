pump_update_resume_path (xlator_t *this)
{
        const char *resume_path = NULL;

        resume_path = pump_get_resume_path (this);

        if (resume_path) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "Found a path to resume from: %s",
                        resume_path);

        }else {
                gf_log (this->name, GF_LOG_DEBUG,
                        "Did not find a path=> setting to '/'");
                pump_set_resume_path (this, "/");
        }

        pump_change_state (this, PUMP_STATE_RESUME);

        return 0;
}
