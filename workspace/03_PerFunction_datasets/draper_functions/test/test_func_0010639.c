app_plan_opencl(
    SCHEDULER_REQUEST& sreq, const char* plan_class, HOST_USAGE& hu
) {


    const char *p=plan_class+strlen(plan_class);
    while (isnum(p[-1])) {
        p--;
    }
    int ver=atoi(p);
    if (config.debug_version_select) {
        log_messages.printf(MSG_NORMAL,
            "[version] plan_class %s uses OpenCl version %d\n",
            plan_class,
            ver
        );
    }
    if (strstr(plan_class, "nvidia")) {
        COPROC_NVIDIA& c = sreq.coprocs.nvidia;
        if (!c.count) return false;
        if (!c.have_opencl) return false;
        if (strstr(plan_class,"opencl_nvidia") == plan_class) {
            return opencl_check(
                c, hu,
                ver,
                OPENCL_NVIDIA_MIN_RAM,
                1,
                .01,
                .14
            );
        } else {
            log_messages.printf(MSG_CRITICAL,
                "Unknown plan class: %s\n", plan_class
            );
            return false;
        }
    } else if (strstr(plan_class, "ati")) {
        COPROC_ATI& c = sreq.coprocs.ati;
        if (!c.count) {
            if (config.debug_version_select) {
                log_messages.printf(MSG_NORMAL,
                    "[version] [opencl] HOST has no ATI/AMD GPUs\n"
                );
            }
            return false;
        }

        if (!c.have_opencl) {
            if (config.debug_version_select) {
                log_messages.printf(MSG_NORMAL,
                    "[version] [opencl] GPU/Driver/BOINC revision doesn not support OpenCL\n"
                );
            }
            return false;
        }

        if (strstr(plan_class,"opencl_ati") == plan_class) {
            return opencl_check(
                c, hu,
                ver,
                OPENCL_ATI_MIN_RAM,
                1,
                .01,
                .14
            );
        } else {
            log_messages.printf(MSG_CRITICAL,
                "[version] [opencl] Unknown plan class: %s\n", plan_class
            );
            return false;
        }

    } else if (strstr(plan_class, "intel_gpu")) {
        COPROC_INTEL& c = sreq.coprocs.intel_gpu;
        if (!c.count) {
            if (config.debug_version_select) {
                log_messages.printf(MSG_NORMAL,
                    "[version] [opencl] HOST has no INTEL GPUs\n"
                );
            }
            return false;
        }

        if (!c.have_opencl) {
            if (config.debug_version_select) {
                log_messages.printf(MSG_NORMAL,
                    "[version] [opencl] GPU/Driver/BOINC revision doesn not support OpenCL\n"
                );
            }
            return false;
        }


        if (strstr(plan_class,"opencl_intel_gpu") == plan_class) {
            return opencl_check(
                c, hu,
                ver,
                OPENCL_INTEL_GPU_MIN_RAM,
                1,
                .1,
                .2
            );
        } else {
            log_messages.printf(MSG_CRITICAL,
                "[version] [opencl] Unknown plan class: %s\n", plan_class
            );
            return false;
        }


    } else {
        log_messages.printf(MSG_CRITICAL,
            "[version] [opencl] Unknown plan class: %s\n", plan_class
        );
        return false;
    }
}
