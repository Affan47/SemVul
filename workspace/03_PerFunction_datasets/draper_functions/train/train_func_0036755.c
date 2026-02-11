push_machine_assert(PPGPushMachine *pm)
{
    gw_assert(pm);
    gw_assert(pm->pi_push_id);
    gw_assert(pm->push_id >= 0);
    gw_assert(pm->session_id >= 0);
    gw_assert(pm->addr_tuple);
    gw_assert(pm->trusted == 1 || pm->trusted == 0);
    gw_assert(pm->authenticated  == 1 || pm->authenticated == 0);
}
