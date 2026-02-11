vi_process_googled(struct vih *vih, char *req, char *agent, time_t age)
{
        if (vi_is_googlebot_agent(agent)) {
	    return vi_replace_if_newer(&vih->googled, req, age);
        } else if (vi_is_adsensebot_agent(agent)) {
	    return vi_replace_if_newer(&vih->adsensed, req, age);
        }
        return 0;
}
