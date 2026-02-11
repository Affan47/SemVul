fini (xlator_t *this)
{
        if (!this)
                return;

        gf_log (this->name, GF_LOG_INFO,
                "trace translator unloaded");
        return;
}
