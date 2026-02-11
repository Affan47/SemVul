mark_edf_misses (int ncpus, vector<IP_RESULT>& ip_results){
    vector<IP_RESULT>::iterator ipp_it;
    double booked_to[MAX_CPUS];
    int j;

    log_msg(DETAIL, "[edf_detail] mark_edf_misses\n");


    for (j=0; j<ncpus; j++) {
        booked_to[j] = 0;
    }


    sort(ip_results.begin(), ip_results.end(), lessthan_deadline);


    for (unsigned int i=0; i<ip_results.size(); i++) {
        IP_RESULT& r = ip_results[i];


        double lowest_booked_time = booked_to[0];
        int lowest_booked_cpu = 0;
        for (j=1; j<ncpus; j++) {
            if (booked_to[j] < lowest_booked_time) {
                lowest_booked_time = booked_to[j];
                lowest_booked_cpu = j;
            }
        }

        booked_to[lowest_booked_cpu] += r.cpu_time_remaining;
        log_msg(DETAIL, "[edf_detail]   running %s on cpu %d; finishes at %.2f\n",
            r.name, lowest_booked_cpu, booked_to[lowest_booked_cpu]/TIME_SCALE
        );
        if (booked_to[lowest_booked_cpu] > r.computation_deadline) {
            r.misses_deadline = true;
            r.estimated_completion_time = booked_to[lowest_booked_cpu];
            log_msg(DETAIL, "[edf_detail]   %s misses_deadline; est completion %.2f\n",
                r.name, booked_to[lowest_booked_cpu]/TIME_SCALE
            );
        } else {
            r.misses_deadline = false;
            log_msg(DETAIL, "[edf_detail]   %s makes deadline; est completion %.2f\n",
                r.name, booked_to[lowest_booked_cpu]/TIME_SCALE
            );


        }
    }
}
