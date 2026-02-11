ap_mpm_pod_killpg(ap_pod_t *pod, int num)
{
    int i;
    apr_status_t rv = APR_SUCCESS;


    for (i = 0; i < num && rv == APR_SUCCESS; i++) {
        rv = dummy_connection(pod);
    }
}
