find_best_opencls(
    bool use_all,
    vector<OPENCL_DEVICE_PROP> &opencls,
    vector<int>& ignore_dev
) {
    unsigned int i;


    bool first = true;
    for (i=0; i<opencls.size(); i++) {
        if (in_vector(opencls[i].device_num, ignore_dev)) {
            opencls[i].is_used = COPROC_IGNORED;
            continue;
        }
        bool is_best = false;
        if (first) {
            is_best = true;
            first = false;
        } else if (opencl_compare(opencls[i], opencl_prop, false) > 0) {
            is_best = true;
        }
        if (is_best) {

            opencl_prop = opencls[i];
            device_num = opencls[i].device_num;
            peak_flops = opencls[i].peak_flops;
            have_opencl = true;
        }
    }


    count = 0;
    opencl_device_count = 0;
    for (i=0; i<opencls.size(); i++) {
        if (in_vector(opencls[i].device_num, ignore_dev)) {
            opencls[i].is_used = COPROC_IGNORED;
            continue;
        }
        if (use_all || !opencl_compare(opencls[i], opencl_prop, true)) {
            device_nums[count++] = opencls[i].device_num;
            opencl_device_indexes[opencl_device_count] = opencls[i].opencl_device_index;
            opencl_device_ids[opencl_device_count++] = opencls[i].device_id;
            opencls[i].is_used = COPROC_USED;
        }
    }
}
