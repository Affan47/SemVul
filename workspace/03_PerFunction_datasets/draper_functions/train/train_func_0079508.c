update_n_jobs_today() {
    for (unsigned int i=0; i<g_wreq->host_app_versions.size(); i++) {
        DB_HOST_APP_VERSION& hav = g_wreq->host_app_versions[i];
        update_quota(hav);
    }
}
