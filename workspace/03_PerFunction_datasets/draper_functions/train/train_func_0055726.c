scale_versions(APP& app, double avg) {
    for (unsigned int j=0; j<app_versions.size(); j++) {
        APP_VERSION& av = app_versions[j];
        if (av.appid != app.id) continue;
        if (av.pfc.n < MIN_VERSION_SAMPLES) continue;

        av.pfc_scale= avg/av.pfc.get_avg();
        PLATFORM* p = lookup_platform(av.platformid);
        printf("updating scale factor for (%s %s)\n",
             p->name, av.plan_class
        );
        printf(" n: %f avg PFC: %f new scale: %f\n",
            av.pfc.n, av.pfc.get_avg(), av.pfc_scale
        );
    }
    app.min_avg_pfc = avg;
}
