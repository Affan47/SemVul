orte_sensor_base_start(orte_jobid_t job)
{
    orte_sensor_active_module_t *i_module;
    int i;

    opal_output_verbose(5, orte_sensor_base_framework.framework_output,
                        "%s sensor:base: starting sensors",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));


    for (i=0; i < orte_sensor_base.modules.size; i++) {
        if (NULL == (i_module = (orte_sensor_active_module_t*)opal_pointer_array_get_item(&orte_sensor_base.modules, i))) {
            continue;
        }
        mods_active = true;
        if (NULL != i_module->module->start) {
            i_module->module->start(job);
        }
    }

    if (mods_active && !orte_sensor_base.active) {

        orte_sensor_base.samples = OBJ_NEW(opal_buffer_t);


        orte_sensor_base.active = true;
        opal_event_evtimer_set(orte_event_base, &orte_sensor_base.sample_ev,
                               orte_sensor_base_sample, NULL);
        opal_event_evtimer_add(&orte_sensor_base.sample_ev, &orte_sensor_base.rate);
    }
    return;
}
